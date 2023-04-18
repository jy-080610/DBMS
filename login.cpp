//
// Created by lx on 2023/4/6.
//
//登录注册界面需要wjx实现

/**
 * 1.实现用户注册登录
 * 2.实现登录注册时的检查
 */
#include "login.h"
#include "qdebug.h"
#include "qmessagebox.h"
#include "qfile.h"
#include "qdir.h"
#include<QCryptographicHash>//加密头文件,QCryptographicHash类的主要作用：对数据进行加密



login::login() {//构造函数
    QDir *dir = new QDir(QDir::currentPath());//获取当前路径
    dir->cdUp();//返回上一级目录
    path =dir->path()+"/DBMS/data";//用户信息文件路径
}

/**
* 用户登录时判断密码是否正确
*/

bool login::checkLog(QString dbname,QString username,QString psd)
{
    //管理员
    qDebug()<<dbname;
    if(dbname=="管理员"){
        QString cpath=path+"/sys/admin.txt";//管理员信息文件路径
        QString cname,cpas;//用户名和密码
        QFile file;
        qDebug()<<cpath;

        //密码加密

    }
}
//用户注册时判断用户名是否已存在
int login::checkError(QString dbname, QString username, QString psd1, QString psd2) {
    if (psd1 != psd2) {
        return 4;//输入密码前后两次不一致
    }
    if ((username.length() < 4) || (psd1.length() < 4)) {//用户名和密码长度小于4
        return 3;
    }

    if (username.contains(",") || username.contains("，") || psd1.contains(",") ||
        psd1.contains("，")) {//用户名和密码中不能包含逗号
        return 2;
    }

    // 目标文件路径
    QString cpath = path + "/" + dbname + "/userinfo.txt";
    QFile   file;

    if (file.exists(cpath)) {
        qDebug() << "userinfo文件存在";
        QFile   userFile(cpath);
        QString lineInf; // 存储一名用户的信息

        if (!userFile.open(QIODevice::ReadOnly)) {
            qDebug() << "userinfo文件打开失败";
            return false;
        }
        QTextStream readInf(&userFile); // 读取用户信息
        QStringList userList;

        // 判断当前注册的用户名是否重复
        while (!readInf.atEnd()) {
            lineInf = readInf.readLine();
            userList = lineInf.split(",");

            if ((username == userList[0])) {
                userFile.close();
                return 1;
            }
        }
        userFile.close();
    }
    return 0;

}
//注册好后插入数据信息
void login::insert2File(QString, QString, QString) {

}
