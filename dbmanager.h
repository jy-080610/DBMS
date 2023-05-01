

#ifndef DBMS_DBMANAGER_H
#define DBMS_DBMANAGER_H
//数据库管理类--数据读写/日志记录/数据库创建记录/数据库删除记录
#include <QString>
#include "qdatetime.h"
#include"selectdatabase.h"
using namespace std;
typedef struct dataBase{
    char dbname[128];//数据库名称
    bool type;//数据库类型
    char dbpath[256];//数据库路径
    QDateTime crtime;//数据库创建时间
}database;//数据库信息结构体

class dbmanager {
public:
    dbmanager();//构造函数
    void myCreateDataBase(QString dbname1);;//创建数据库
    void myDeteleDataBase(QString dbname2);//删除数据库
    void writeDBinto(struct dataBase my_database);//将创建数据库信息写入日志文件
    void writedelDBinto(QString dbname3);//将删除数据库信息写入日志文件

private:
    QString path;//数据库文件路径
    QString dataPath;//数据文件路径
};


#endif //DBMS_DBMANAGER_H
