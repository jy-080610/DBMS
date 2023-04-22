//
//表的创建与删除
//

#include "managetablebysql.h"
#include "qdir.h"
#include "qdebug.h"
#include "tablemanager.h"
#include "qmessagebox.h"
#include "privilegemanager.h"
managetablebysql::managetablebysql() {

}
//创建表
void managetablebysql::createTable(QString tableName) {
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    QString dirPath = dir->path() + "/DBMS/data/sys/curuse.txt";
    QFile file(dirPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString str = read.readLine();
    list = str.split(",");
    file.close();
    if (tableName != "") {
        TableManager TM(list[0], list[1]);
        TM.tableCreator(tableName);
        QMessageBox::information(0,
                                 "通知",
                                 "表已经创建",
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::Cancel | QMessageBox::Escape, 0);
    } else {
        QMessageBox::critical(0, "错误", "表名不能为空",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }

}
//删除表
void managetablebysql::deleteTable(QString tableName) {
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    QString dirPath = dir->path() + "/DBMS/data/sys/curuse.txt";

    QFile file(dirPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();
    list = str.split(",");
    file.close();

    if (tableName != "") {
        TableManager TM(list[0], list[1]);
        TM.tableDelete(tableName);
        QMessageBox::information(0,
                                 "通知",
                                 "表已经删除",
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::Cancel | QMessageBox::Escape, 0);
    } else {
        QMessageBox::critical(0, "错误", "表名不能为空",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}
