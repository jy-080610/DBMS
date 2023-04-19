#include "fieldmanager.h"
#include "ui_fieldmanager.h"
#include "QFileDialog"
#include "qdebug.h"
#include "tablemanager.h"
#include "qmessagebox.h"
#include "dataoperation.h"

FieldManager::FieldManager(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::FieldManager)
{
    ui->setupUi(this);

    // 初始化目录文件路径
    initDir();
}

FieldManager::~FieldManager()
{
    delete ui;
}

/*
 * @Brief:  初始化文件目录
 * @Return: NULL
 */
void FieldManager::initDir()
{
    // 以只读方式打开存放用户名和数据库名的文件，并给所需变量依次赋值
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QFile file(dir->path() + "/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "initDir文件打开失败";
    }
//    QTextStream read(&file);
//    QStringList list;
//    QString     str = read.readLine();
//
//    qDebug() << "用户信息" + str;
//
//    list = str.split(",");
//
//    // 初始化用户名，数据库名和数据库路径
//    userName = list[0];
//    dbName = list[1];
//    dirPath = dir->path() + "/data/" + list[1];
    file.close();
}

/*
 * @Brief:  判断当前表文件是否已经存在，防止重复创建
 * @Return: 存在为真，不存在为假
 */
bool FieldManager::isTableExist()
{
    tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +
                this->ui->path->text() + ".tdf";

    QFile tempFile(tablePath);

    return tempFile.exists();
}

/*
 * @Brief:  增加字段
 * @Return: NULL
 */
void FieldManager::on_add_clicked()
{
    // 容错处理，防止输入为空或字段重复
    if ((this->ui->path->text() == "") ||
        this->ui->fieldNameEdit->text().isEmpty() ||
        (this->ui->fieldNameEdit->text() == "")) {
        QMessageBox::critical(nullptr, "错误", "字段名为空",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    if (isDuplicate(this->ui->fieldNameEdit->text())) {
        QMessageBox::critical(nullptr, "错误", "当前字段已存在",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 定位到对应的文件路径
    tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +
                this->ui->path->text() + ".tdf";

    QFile checkFile(tablePath);

    if (!checkFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }

    QTextStream read(&checkFile);

    QString isPK, isNull;

    // 若当前插入的字段被标注为主键，则判断已有字段中是否已存在主键
    if (this->ui->isPK->isChecked()) {
        QString textInfo = read.readAll();

        if (textInfo.contains(",主键,")) {
            QMessageBox::critical(nullptr, "错误", "此表中已存在主键",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }
        isPK = "主键";
    } else {
        isPK = "非主键";
    }

    if (this->ui->isNull->isChecked()) {
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
    insertInfo += this->ui->fieldNameEdit->text() + "," +
                  this->ui->dataType->currentText() + "," +
                  isPK + "," +
                  isNull + "\n";
    write << insertInfo;
    file.close();

    // 展示信息
    display();
    addComma2trd(); // 向数据记录表中添加一列

    // 更新表定义文件
    TableManager TM(userName, dbName);

    TM.tableModifier(this->ui->path->text(), 1);
}

/*
 * @Brief:  修改字段
 * @Return: NULL
 */
void FieldManager::on_modify_clicked()
{
    // 容错判断
    if (this->ui->path->text().isEmpty() ||
        this->ui->fieldNameEdit->text().isEmpty() ||
        (this->ui->fieldNameEdit->text() == "")) {
        QMessageBox::critical(nullptr, "错误", "字段名为空",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 定位文件路径
    tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +
                this->ui->path->text() + ".tdf";


    // 以只读方式打开原文件
    QFile checkFile(tablePath);

    if (!checkFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream checkText(&checkFile);

    // 检查判断，若将该字段修改为主键，但表中已存在，则提示错误
    if (this->ui->isPK->isChecked()) {
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
    QString afterDelPath = dirPath + "/table/" + this->ui->path->text() +
                           "/modify.tdf";
    QFile writeFile(afterDelPath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QStringList list;
    QString     str, modInfo, isPK, isNull;

    if (this->ui->isPK->isChecked()) {
        isPK = "主键";
    } else {
        isPK = "非主键";
    }

    if (this->ui->isNull->isChecked()) {
        isNull = "可为空";
    } else {
        isNull = "非空";
    }

    modInfo = this->ui->fieldNameEdit->text();

    // 以只读方式打开原文件
    QFile readFile(tablePath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);

    qDebug() << "正在查找要替换的内容";

    // 依次读取原文件内容，当遇到修改值时进行替换，然后逐行写入新文件
    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");

        if (list[0] == modInfo) {
            modInfo += "," +
                       this->ui->dataType->currentText() + "," +
                       isPK + "," +
                       isNull + "\n";
            qDebug() << "modinfo" + modInfo;
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
    display();

    // 更新定义表
    TableManager TM(userName, dbName);

    TM.tableModifier(this->ui->path->text(), 3);
}

/*
 * @Brief:  删除字段
 * @Return: NULL
 */
void FieldManager::on_dele_clicked()
{
    // 容错处理
    if (this->ui->path->text().isEmpty() ||
        this->ui->fieldNameEdit->text().isEmpty() ||
        (this->ui->fieldNameEdit->text() == "")) {
        QMessageBox::critical(0, "错误", "字段名为空",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 定位文件路径，以只读方式打开
    tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +
                this->ui->path->text() + ".tdf";
    QFile readFile(tablePath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);

    // 创建新文件，来存储修改后的文件内容
    QString afterDelPath = dirPath + "/table/" + this->ui->path->text() +
                           "/del.tdf";
    QFile writeFile(afterDelPath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QStringList list;
    QString     str, delInfo;

    // 获取删除的字段名
    delInfo = this->ui->fieldNameEdit->text();

    // 要删除的那一列的列号
    int deleColId = 1;

    // 执行删除操作，并记录要删除的字段是哪一列
    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");

        if (list[0] == delInfo) {
            qDebug() << "delecolid=" << deleColId;

            // 删除相应的数据
            removedata(deleColId - 1);
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

    display();

    // 更新定义表
    TableManager TM(userName, dbName);

    TM.tableModifier(this->ui->path->text(), 4);
}

/*
 * @Brief:  展示表结构按钮
 * @Return: NULL
 * @Todo:   根据后续的表格设计再增加展示信息
 */
void FieldManager::on_display_clicked()
{
    if (this->ui->path->text().isEmpty() ||
        (this->ui->path->text() == "")) {
        QMessageBox::critical(nullptr, "错误", "请输入表名",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    display();
}

/*
 * @Brief:  展示表结构，将字段信息展示在UI的table上
 * @Return: NULL
 */
void FieldManager::display()
{
    ui->tableWidget->clear();

    // 当指定的表存在时，进行展示操作
    if (isTableExist()) {
        // 以只读方式打开对应文件
        tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +
                    this->ui->path->text() + ".tdf";
        QFile readFile(tablePath);

        if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream read(&readFile);
        QString     str, info;
        QStringList strlist, headlist;

        // 表头赋值
        headlist << "字段名" << "数据类型" << "是否为主键" << "可否为空";

        // 定义行号和列号
        int rownum = 0, colnum = 4;
        ui->tableWidget->setColumnCount(colnum);

        // 逐行读取文件信息并给UI赋值
        while (!read.atEnd()) {
            str = read.readLine();

            if (str != "") {
                ui->tableWidget->setRowCount(rownum + 1);
                strlist = str.split(",");

                for (int i = 0; i < colnum; i++) {
                    ui->tableWidget->setItem(rownum, i,
                                             new QTableWidgetItem(strlist[i]));
                }
                rownum++;
            }
        }
        readFile.close();

        // 添加表头
        ui->tableWidget->setHorizontalHeaderLabels(headlist);
    }
}

/*
 * @Brief:  判断要添加的字段名是否已经存在
 * @Param:  fieldName 要添加的字段名
 * @Return: 存在为真，否则为假
 */
bool FieldManager::isDuplicate(QString fieldName)
{
    // 以只读方式打开文件
    tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +
                this->ui->path->text() + ".tdf";
    qDebug() << tablePath;
    QFile file(tablePath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return false;
    }
    QTextStream read(&file);
    QStringList list;
    QString     readinfo;

    // 将要添加的字段依次和已存在的字段进行比对
    while (!read.atEnd()) {
        readinfo = read.readLine();
        list = readinfo.split(",");

        if (fieldName == list[0]) {
            return true;
        }
    }

    return false;
}

/*
 * @Brief:在添加字段后调用此函数保证字段和数据的列数相同
 * @Return: NULL
 */
void FieldManager::addComma2trd()
{
    // 以只读方式打开指定文件
    QString trdPath = dirPath + "/table/" + this->ui->path->text() + "/" +
                      this->ui->path->text() + ".trd";
    QFile readFile(trdPath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);

    // 定义修改后的新文件
    QString afterAddPath = dirPath + "/table/" + this->ui->path->text() +
                           "/modify.trd";
    QFile writeFile(afterAddPath);

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
 * @Return: NULL
 */
void FieldManager::removedata(int datacol) {
    // 以下操作与之前均相同，依次打开原文件和存储修改后信息的新文件
    QString trdPath = dirPath + "/table/" + this->ui->path->text() + "/" +
                      this->ui->path->text() + ".trd";
    QFile readFile(trdPath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);
    QString     afterDeletePath = dirPath + "/table/" + this->ui->path->text() +
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

// 当主键点击时，同步更改非空判断
void FieldManager::on_isPK_clicked()
{
    if (ui->isPK->isChecked()) {
        ui->isNull->setChecked(false);
    }
}

void FieldManager::on_isNull_clicked()
{
    if (ui->isPK->isChecked()) {
        ui->isNull->setChecked(false);
    } else if (ui->isNull->isChecked()) {
        ui->isNull->setChecked(true);
    } else {
        ui->isNull->setChecked(false);
    }
}
