//注册
#ifndef DBMS_LOGIN_H
#define DBMS_LOGIN_H
#include "qstring.h"
typedef struct user{
    QString username;//用户名
    QString psd;//密码
    QString privilege;//权限
}user;//用户信息结构体


class login {
public:
    login();//构造函数

    //用户登录时判断密码是否正确
    bool checkLog(QString,QString,QString);

    //用户注册时判断用户名是否已存在
    int checkError(QString,QString,QString,QString);

    //注册好后插入数据信息
    void insert2File(QString,QString,QString);

private:
    QString path;//用户信息文件路径

};


#endif //DBMS_LOGIN_H
