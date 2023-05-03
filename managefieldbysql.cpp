//
// 字段管理--属性在文件中存储格式格式: 表名，列名，数据类型，是否为主键，是否非空
//

#include "managefieldbysql.h"
#include "qmessagebox.h"
#include "qdebug.h"
#include "tablemanager.h"

ManageFieldBySql::ManageFieldBySql() {
    initDir();//初始化目录

}
void ManageFieldBySql::initDir() {
    QDir *dir=new QDir(QDir::currentPath());
    dir->cdUp();//返回上一层目录
    QFile file(dir->path() + "/data/sys/curuse.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString str =read.readLine();

    list=str.split(",");
    userName=list[0];
    dbName=list[1];
    dirPath=dir->path()+"/data/"+list[1];
    file.close();
}
//向文件中添加属性字段，格式: 表名，列名，数据类型，是否为主键，是否非空
void ManageFieldBySql::addField2tdf(QStringList keywordList) {
    if((keywordList[1]=="")||(keywordList[2]=="")||(keywordList[3]=="")){
        QMessageBox::critical(0,"错误","输入不能为空",QMessageBox::Ok|QMessageBox::Default,QMessageBox::Cancel|QMessageBox::Escape,0);
        return;
    }
    if(isDuplicate(keywordList)){
        QMessageBox::critical(0,"错误","属性名重复",QMessageBox::Ok|QMessageBox::Default,QMessageBox::Cancel|QMessageBox::Escape,0);
        return;
    }

    tablePath = dirPath + "/table/" + keywordList[1] + "/" +keywordList[1] + ".tdf";    QFile checkFile(tablePath);
    if(!checkFile.open(QIODevice::Append|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream read(&checkFile);
    QString isPK;
    QString isNull;
    if(keywordList[4]=="") {
        isPK = "非主键";

    }else{
        QString textInfo=read.readAll();//读取文件中的内容
        if(textInfo.contains("主键")){
            QMessageBox::critical(0,"错误","主键已存在",QMessageBox::Ok|QMessageBox::Default,QMessageBox::Cancel|QMessageBox::Escape,0);
            return;
        }
        isPK="主键";
    }
    if ((keywordList[5]=="")&&(keywordList[4]=="")) {
        isNull = "可为空";
    }else{
        isNull="非空";
    }
    QFile file(tablePath);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream write(&file);
    QString insertInfo="";
    insertInfo=keywordList[2]+","+keywordList[3]+","+isPK+","+isNull+"\n";
    write<<insertInfo;
    file.close();
    addComma2trd(keywordList);//向trd文件中添加新的一列
    TableManager TM(userName,dbName);
    TM.tableModifier(keywordList[1],1);
}
//keywordList为删除的属性字段信息
void ManageFieldBySql::deleFileFromtdf(QStringList keywordList) {

    if ((keywordList[1] == "") ||
        (keywordList[2] == "")) {
        QMessageBox::critical(0, "错误", "输入不能为空",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    tablePath = dirPath + "/table/" + keywordList[1] + "/" +keywordList[1] + ".tdf";
    qDebug()<<tablePath;
    QFile readFile(tablePath);
    if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream read(&readFile);
    QString afterDelPath = dirPath + "/table/" + keywordList[1] +"/del.tdf";
    QFile writeFile(afterDelPath);
    if(!writeFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream write(&writeFile);
    QStringList list;
    QString str;
    QString delInfo;
    //要删除的属性名
    delInfo=keywordList[2];
    int deleColId=1;//要删除的列号
    while(!read.atEnd()){
        str=read.readLine();
        list=str.split(",");
        if(list[0]==delInfo){
            removedata(deleColId-1,keywordList[1]);
        }else{
            write<<str+"\n";
            deleColId++;
        }
    }

    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(tablePath);

    //更新定义表
    TableManager TM(userName,dbName);
    TM.tableModifier(keywordList[1],4);
}
//根据指定的信息修改表的字段信息
void ManageFieldBySql::modifyInfo2tb(QStringList  keywordList) {
    if((keywordList[1]=="")||(keywordList[2]=="")){
        QMessageBox::critical(0,"错误","输入不能为空",QMessageBox::Ok|QMessageBox::Default,QMessageBox::Cancel|QMessageBox::Escape,0);
        return;
    }
    tablePath = dirPath + "/table/" + keywordList[1] + "/" +keywordList[1] + ".tdf";
    QFile checkFile(tablePath);
    if(!checkFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream checkText(&checkFile);
    //检查表中是否存在主键，若主键存在则不允许修改
    if (keywordList.contains("primary key") ||
        keywordList.contains("PRIMARY KEY")) {
        QString textInfo = checkText.readAll();

        if (textInfo.contains(",主键,")) {
            QMessageBox::critical(0, "错误", "主键已存在",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }
    }
    checkFile.close();
    QString afterModifyPath = dirPath + "/table/" + keywordList[1] +"/modify.tdf";
    QFile writeFile(afterModifyPath);
        if(!writeFile.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败";
        }
        QTextStream write(&writeFile);
        QStringList list;
        QString str;
        QString modInfo;

        QString isPK;
        QString isNull;
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
    modInfo = keywordList[2] ;
    QFile readFile(tablePath);
    if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream read(&readFile);
    while(!read.atEnd()){
        str=read.readLine();
        list=str.split(",");
        if(list[0]==modInfo){
            isPK=list[2]=="主键"?"主键":isPK;
            modInfo+=","+list[1]+","+isPK+","+isNull+"\n";
            write<<modInfo;
    }else{
            write<<str+"\n";
        }
    }

    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(tablePath);
    //更新定义表
    TableManager TM(userName,dbName);
    TM.tableModifier(keywordList[1],3);
}


//是否有重复属性
bool ManageFieldBySql::isDuplicate(QStringList keywordList) {

    tablePath = dirPath + "/table/" + keywordList[1] + "/" +keywordList[1] + ".tdf";
    QFile file(tablePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return false;
    }
    QTextStream read(&file);
    QStringList list;
    QString     readinfo;

    // 无重复则返回true
    while (!read.atEnd()) {
        readinfo = read.readLine();
        list = readinfo.split(",");
        if (keywordList[2] == list[0]) {
            return true;
        }
    }
    return false;
}

void ManageFieldBySql::removedata(int datacol, QString tablename) {//根据删字段列号来删除对应的数据列除的
    QString trdPath = dirPath + "/table/" + tablename + "/" +tablename + ".trd";
    QFile readFile(trdPath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);
    QString     afterDeletePath = dirPath + "/table/" + tablename +"/modify.trd";
    QFile writeFile(afterDeletePath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QString  str1;
    QString str2;
    QStringList list;

    qDebug() << "datacol=" << datacol;
    int col = datacol;

    // 从旧文件逐行读取信息,将每一行信息依次进行修改，删除对应的列后写入到新文件中
    while (!read.atEnd()) {
        str2 = "";
        str1 = read.readLine();
        list = str1.split(",");
        qDebug() << "col=" << col;
        list.removeAt(col);
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
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(trdPath);
}

//添加字段后调用此函数保证字段和数据的列数相同
void ManageFieldBySql::addComma2trd(QStringList keywordList) {
    QString trdPath = dirPath + "/table/" + keywordList[1] + "/" +keywordList[1] + ".trd";
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
    while (!read.atEnd()) {
        str = read.readLine();
        write << str + ",\n";
    }
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(trdPath);
}
