//
// Created by Asus on 2023/4/17.
//

#include "managetablebysql.h"
#include "qdir.h"
#include "qdebug.h"
#include "tablemanager.h"
#include "qmessagebox.h"
#include "privilegemanager.h"

//通过SQL语句对表进行管理

ManageTableBySql::ManageTableBySql()
{}

/*
 * @Brief:  创建表
 * @Param:  tableName 表名
 * @Return: NULL
 */
void ManageTableBySql::createTable(QString tableName)
{
    // 获取当前正在使用的用户和数据库，从而确定创建目录
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString dirPath = dir->path() + "/DBMS/data/sys/curuse.txt";

    // 以只读方式打开文件
    QFile file(dirPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }

    QTextStream read(&file);
    QStringList list;

    // 逐行读取文件信息
    QString str = read.readLine();

    list = str.split(",");
    file.close();

    // 若提取到的表名有效，则进行创建
    if (tableName != "") {
        TableManager TM(list[0], list[1]);
        TM.tableCreator(tableName);
        QMessageBox::information(0,
                                 "通知",
                                 "创建成功",
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::Cancel | QMessageBox::Escape, 0);
    } else {
        QMessageBox::critical(0, "错误", "请确定表名合法",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

/*
 * @Brief:  删除表
 * @Param:  tableName 表名
 * @Return: NULL
 */
void ManageTableBySql::deleteTable(QString tableName)
{
    // 获取当前正在使用的用户和数据库，从而确定创建目录
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

    // 若提取到的表名有效，则进行删除
    if (tableName != "") {
        TableManager TM(list[0], list[1]);
        TM.tableDelete(tableName);
        QMessageBox::information(0,
                                 "通知",
                                 "删除成功",
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::Cancel | QMessageBox::Escape, 0);
    } else {
        QMessageBox::critical(0, "错误", "请确定表名合法",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}
