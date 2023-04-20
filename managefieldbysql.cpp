//
// Created by Asus on 2023/4/17.
//
#include "managefieldbysql.h"
#include "qmessagebox.h"
#include "tablemanager.h"

ManageFieldBySql::ManageFieldBySql()
{
    initDir();
}

/*
 * @Brief:  初始化文件路径
 * @Return: NULL
 */
void ManageFieldBySql::initDir()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QFile file(dir->path() + "/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "initDir文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    qDebug() << "用户信息" + str;

    list = str.split(",");

    // 初始化用户名、密码、数据库路径
    userName = list[0];
    dbName = list[1];
    dirPath = dir->path() + "/data/" + list[1];
    file.close();
}

/*
 * @Brief:  向tdf表中增加字段
 * @Param:  keywordList 包含关键字的列表
 *          内容分别为：
 *          类型，表名，列名，数据类型，主键，非空
 * @Return: NULL
 */
void ManageFieldBySql::addField2tdf(QStringList keywordList)
{
    // 容错处理，防止输入为空或字段重复
    if ((keywordList[1] == "") ||
        (keywordList[2] == "") ||
        (keywordList[3] == "")) {
        QMessageBox::critical(nullptr, "错误", "请检查基本信息是否正确",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    if (isDuplicate(keywordList)) {
        QMessageBox::critical(nullptr, "错误", "当前字段已存在",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 定位到对应的文件路径
    tablePath = dirPath + "/table/" + keywordList[1] + "/" +
                keywordList[1] + ".tdf";


    QFile checkFile(tablePath);

    if (!checkFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }

    QTextStream read(&checkFile);

    QString isPK, isNull;

    if (keywordList[4] == "") {
        isPK = "非主键";
    } else {
        QString textInfo = read.readAll();

        if (textInfo.contains(",主键,")) {
            QMessageBox::critical(nullptr, "错误", "此表中已存在主键",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }
        isPK = "主键";
    }

    if (((keywordList[5] == "") && (keywordList[4] == ""))) {
        isNull = "可为空";
    } else {
        isNull = "非空";
    }


    // 以追加方式打开文件
    QFile file(tablePath);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream write(&file);
    QString     insertInfo = "";

    // 将键的信息写入文件
    insertInfo += keywordList[2] + "," +
                  keywordList[3] + "," +
                  isPK + "," +
                  isNull + "\n";
    write << insertInfo;
    file.close();
    addComma2trd(keywordList); // 向数据记录表中添加一列

    // 更新表定义文件
    TableManager TM(userName, dbName);

    TM.tableModifier(keywordList[1], 1);
}

/*
 * @Brief:  删除指定的字段信息
 * @Param:  keywordList 要删除的字段信息
 * @Return: NULL
 */
void ManageFieldBySql::deleFileFromtdf(QStringList keywordList)
{
    // 容错处理
    if ((keywordList[1] == "") ||
        (keywordList[2] == "")) {
        QMessageBox::critical(0, "错误", "请检查基本信息是否正确",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 定位文件路径，以只读方式打开
    tablePath = dirPath + "/table/" + keywordList[1] + "/" +
                keywordList[1] + ".tdf";
    qDebug() << "当前表的路径为：" + tablePath;
    QFile readFile(tablePath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);

    // 创建新文件，来存储修改后的文件内容
    QString afterDelPath = dirPath + "/table/" + keywordList[1] +
                           "/del.tdf";
    QFile writeFile(afterDelPath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QStringList list;
    QString     str, delInfo;

    // 获取删除的字段名
    delInfo = keywordList[2];

    // 要删除的那一列的列号
    int deleColId = 1;

    // 执行删除操作，并记录要删除的字段是哪一列
    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");

        if (list[0] == delInfo) {
            // 删除相应的数据
            removedata(deleColId - 1, keywordList[1]);
        }
        else {
            write << str + "\n";
            deleColId++;
        }
    }

    // 将原文件用新文件替换
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(tablePath);

    // 更新定义表
    TableManager TM(userName, dbName);

    TM.tableModifier(keywordList[1], 4);
}

/*
 * @Brief:  根据指定的信息修改表的字段
 * @Param:  keywordList 要修改的字段信息
 * @Return: NULL
 */
void ManageFieldBySql::modifyInfo2tb(QStringList keywordList)
{
    // 容错判断
    if ((keywordList[1] == "") ||
        (keywordList[2] == "")) {
        QMessageBox::critical(nullptr, "错误", "表名或字段名为空",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 定位文件路径
    tablePath = dirPath + "/table/" + keywordList[1] + "/" +
                keywordList[1] + ".tdf";

    // 以只读方式打开原文件
    QFile checkFile(tablePath);

    if (!checkFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream checkText(&checkFile);

    // 检查判断，若将该字段修改为主键，但表中已存在，则提示错误
    if (keywordList.contains("primary key") ||
        keywordList.contains("PRIMARY KEY")) {
        QString textInfo = checkText.readAll();

        if (textInfo.contains(",主键,")) {
            QMessageBox::critical(nullptr, "错误", "此表中已存在主键",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }
    }
    checkFile.close();

    // 定义修改文件，将原文件内容修改后写入该文件
    QString afterModifyPath = dirPath + "/table/" + keywordList[1] +
                              "/modify.tdf";
    QFile writeFile(afterModifyPath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QStringList list;
    QString     str, modInfo, isPK, isNull;


    if (keywordList.contains("primary key") ||
        keywordList.contains("PRIMARY KEY")) {
        isPK = "主键";
    } else {
        isPK = "非主键";
    }

    if (keywordList.contains("NOT NULL") || keywordList.contains("not null") ||
        (isPK == "主键")) {
        isNull = "非空";
    } else {
        isNull = "可为空";
    }

    modInfo = keywordList[2];

    QFile readFile(tablePath);

    // 以只读方式打开原文件
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);

    // 依次读取原文件内容，当遇到修改值时进行替换，然后逐行写入新文件
    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");

        if (list[0] == modInfo) {
            isPK = list[2] == "主键" ? "主键" : isPK;
            modInfo += "," +
                       list[1] + "," +
                       isPK + "," +
                       isNull + "\n";
            write << modInfo;
        } else {
            write << str + "\n";
        }
    }

    // 将原文件删除，用新文件替代
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(tablePath);

    // 更新定义表
    TableManager TM(userName, dbName);

    TM.tableModifier(keywordList[1], 3);
}

/*
 * @Brief:
 * @Param:  fieldName 要添加的字段名
 * @Return: NULL
 */
bool ManageFieldBySql::isDuplicate(QStringList keywordList)
{
    // 以只读方式打开文件
    tablePath = dirPath + "/table/" + keywordList[1] + "/" +
                keywordList[1] + ".tdf";
    QFile file(tablePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return false;
    }
    QTextStream read(&file);
    QStringList list;
    QString     readinfo;

    // 将要添加的字段依次和已存在的字段进行比对，无重复则返回true
    while (!read.atEnd()) {
        readinfo = read.readLine();
        list = readinfo.split(",");

        if (keywordList[2] == list[0]) {
            return true;
        }
    }

    return false;
}

/*
 * @Brief:  在添加字段后调用此函数保证字段和数据的列数相同
 * @Return: NULL
 */
void ManageFieldBySql::addComma2trd(QStringList keywordList)
{
    // 以只读方式打开指定文件
    QString trdPath = dirPath + "/table/" + keywordList[1] + "/" +
                      keywordList[1] + ".trd";
    QFile readFile(trdPath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);

    // 定义修改后的新文件
    QString afterAddPath = dirPath + "/table/" + keywordList[1] + "/modify.trd";
    QFile   writeFile(afterAddPath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QString     str;


    // 将修改后的内容写入新文件
    while (!read.atEnd()) {
        str = read.readLine();
        write << str + ",\n";
    }

    // 用新文件替换掉旧文件
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(trdPath);
}

/*
 * @Brief:  根据删除的字段列号来删除对应的数据列
 * @Param:  datacol 要删除的数据位于的列
 * @Param:  tablename 要删除的数据位于所在的表
 * @Return: NULL
 */
void ManageFieldBySql::removedata(int datacol, QString tablename) {
    // 以下操作与之前均相同，依次打开原文件和存储修改后信息的新文件
    QString trdPath = dirPath + "/table/" + tablename + "/" +
                      tablename + ".trd";
    QFile readFile(trdPath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);
    QString     afterDeletePath = dirPath + "/table/" + tablename +
                                  "/modify.trd";
    QFile writeFile(afterDeletePath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QString     str1, str2;
    QStringList list;

    qDebug() << "datacol=" << datacol;
    int col = datacol;

    // 从旧文件逐行读取信息,将每一行信息依次进行修改，删除对应的那一列后写入到新文件中
    while (!read.atEnd()) {
        str2 = "";
        str1 = read.readLine();
        list = str1.split(",");
        qDebug() << "col=" << col;
        list.removeAt(col);
        qDebug() << "after remove list=" << list;
        int j;

        for (j = 0; j < list.size(); j++) {
            if (j < list.size() - 1) {
                str2 = str2 + list[j] + ",";
            }
            else if (j == list.size() - 1) {
                str2 = str2 + list[j];
            }
            qDebug() << "str2=" << str2;
        }
        write << str2 + "\n";
    }

    // 新文件替换旧文件
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(trdPath);
}

