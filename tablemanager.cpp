//
// Created by Asus on 2023/4/17.
//

#include <QDateTime>
#include <QMessageBox>
#include "tablemanager.h"


TableManager::TableManager()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    dirPath = dir->path() + "/data";
}

/*
 * @Brief:  构造器
 * @Param:  username 用户名
 * @Param:  dbname   数据库名
 * @Return: NULL
 */
TableManager::TableManager(QString username, QString dbname)
{
    // 初始化变量
    this->username = username;
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    dirPath = dir->path() + "/data/" + dbname;
}

/*
 * @Brief:  判断该表是否已经存在
 * @Param:  tableName 文件名
 * @Return: 存在为真，不存在为假
 */
bool TableManager::isTableExist(QString tableName)
{
    tablePath = dirPath + "/table/" + tableName;
    QDir dir(tablePath);

    if (dir.exists()) {
        return true;
    } else {
        dir.mkdir(tablePath);
        qDebug() << "表文件创建成功";
        return false;
    }
}

/*
 * @Brief:  创建表和基本信息文件
 * @Param:  tableName 文件名
 * @Return: NULL
 */
void TableManager::tableCreator(QString tableName)
{
    if (tableName.length() > 128) return;

    if (isTableExist(tableName)) {
        qDebug() << "表已存在";
        return;
    }

    // 设置时间格式
    QDateTime time = QDateTime::currentDateTime();
    QString   datetime = time.toString("yyyy-MM-dd hh:mm:ss");

    QFile file(tablePath + "/" + tableName + ".tb");

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }

    QTextStream out(&file);

    // name-表名   record_num-行数  field_num-列数  tdf-表定义文件  tic-完整性描述文件
    // trd-记录文件  tid-索引文件 crtime-创建时间  mtime-最后修改时间
    out << "name:" + tableName + "\n";
    out << "record_num:0\n";
    out << "field_num:0\n";
    out << "tdf:" + dirPath + "/table/" + tableName + "/" + tableName + ".tdf\n";
    out << "tic:" + dirPath + "/table/" + tableName + "/" + tableName + ".tic\n";
    out << "trd:" + dirPath + "/table/" + tableName + "/" + tableName + ".trd\n";
    out << "tid:" + dirPath + "/table/" + tableName + "/" + tableName + ".tid\n";
    out << "crtime:" + datetime + "\n";
    out << "mtime:" + datetime + "\n";
    file.close();

    // 依次创建需要用到的表文件
    QStringList strlist;

    strlist << ".tdf" << ".tic" << ".trd" << ".tid";

    for (int i = 0; i < strlist.size(); i++) {
        QFile tempfile(tablePath + "/" + tableName + strlist[i]);
        if (!tempfile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        tempfile.close();
    }
    QFile privilege(tablePath + "/privilege.txt");

    privilege.open(QIODevice::WriteOnly | QIODevice::Append);
    QTextStream outp(&privilege);

    outp << username + ",0,0,0,0,0\n";// 记录用户权限：0-无权限 1-有权限
    privilege.close();
}

/*
 * @Brief:  当用户修改表中的某些字段时，更改对应表描述文件中的字段数、记录数、修改时间或路径
 * @Param:  tableName 表名
 * @Param:  type 操作类型 1-增加字段 2-增加记录 3-修改字段 4-删除字段
 * @Return: null
 */
void TableManager::tableModifier(QString tableName, int type)
{
    // 修改时间
    QDateTime time = QDateTime::currentDateTime();
    QString   datetime = time.toString("yyyy-MM-dd hh:mm:ss");

    // 修改文件的路径
    QString targetPath = dirPath + "/table/" + tableName + "/" + tableName +
                         ".tb";
    QFile readFile(targetPath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&readFile);

    // 修改后的文件
    QFile writeFile(dirPath + "/table/" + tableName + "/modify.tb");

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QStringList strlist;

    QString str;

    // 根据不同的操作类型，进行对应的修改
    switch (type) {
        case 1:

            while (!read.atEnd()) {
                str = read.readLine();

                if (str.contains("field_num")) {
                    strlist = str.split(":");
                    write <<
                          "field_num:" + QString::number(strlist[1].toInt() + 1) + "\n";
                    //更新表格最后修改时间
                    while (!read.atEnd()) {
                        str = read.readLine();
                        if (str.contains("mtime")) {
                            write << "mtime:" + datetime + "\n";
                            break;
                        } else {
                            write << str + "\n";
                        }
                    }

                    break;
                } else {
                    write << str + "\n";
                }
            }
            break;

        case 2:

            while (!read.atEnd()) {
                str = read.readLine();

                if (str.contains("record_num")) {
                    strlist = str.split(":");
                    write <<
                          "record_num:" + QString::number(strlist[1].toInt() + 1) +
                          "\n";

                    //更新表格最后修改时间
                    while (!read.atEnd()) {
                        str = read.readLine();
                        if (str.contains("mtime")) {
                            write << "mtime:" + datetime + "\n";
                            break;
                        } else {
                            write << str + "\n";
                        }
                    }

                    break;
                } else {
                    write << str + "\n";
                }
            }
            break;

        case 3:

            while (!read.atEnd()) {
                str = read.readLine();

                if (str.contains("mtime")) {
                    write << "mtime:" + datetime + "\n";
                    break;
                } else {
                    write << str + "\n";
                }
            }
            break;

        case 4:

            while (!read.atEnd()) {
                str = read.readLine();

                if (str.contains("field_num")) {
                    strlist = str.split(":");
                    write <<
                          "field_num:" + QString::number(strlist[1].toInt() - 1) + "\n";

                    //更新表格最后修改时间
                    while (!read.atEnd()) {
                        str = read.readLine();
                        if (str.contains("mtime")) {
                            write << "mtime:" + datetime + "\n";
                            break;
                        } else {
                            write << str + "\n";
                        }
                    }

                    break;
                } else {
                    write << str + "\n";
                }
            }
            break;

        default:
            return;
    }

    str = read.readAll();
    write << str + "\n";

    // 用修改后的文件替换原文件
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(targetPath);
}

/*
 * @Brief:  删除用户所选的表
 * @Param:  tableName 表名
 * @Return: 成功为ture 失败为false
 */
bool TableManager::tableDelete(QString tableName)
{
    tablePath = dirPath + "/table/" + tableName;

    // 是否传入了空的路径||路径是否存在
    if (tablePath.isEmpty() || !QDir().exists(tablePath)) {
        QMessageBox::critical(nullptr, "critical message", "此表不存在",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);

        return false;
    }

    // 删除该路径下的所有内容
    QFileInfo FileInfo(tablePath);

    if (FileInfo.isFile())     // 如果是文件
        QFile::remove(tablePath);
    else if (FileInfo.isDir()) // 如果是文件夹
    {
        QDir qDir(tablePath);
        qDir.removeRecursively();
    }
    return true;
}

