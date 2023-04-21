//
// 通过sql语句操作数据库
//

#ifndef DBMS_MANAGEDATABYSQL_H
#define DBMS_MANAGEDATABYSQL_H
#include "qstring.h"
#include "qdebug.h"
#include "qstringlist.h"

class managedatabysql {
public:
    managedatabysql();
    void insertData(QStringList);//插入数据
    void deleteData(QStringList);//删除数据
    void updateData(QStringList);//更新数据
    void writeintoLOG(int i,QStringList keywordList);//写入日志

private:
    void initDir();//初始化目录
    int countfield(QString);//计算字段数
    bool hassame(int,QString);//判断是否有重复

    QString dirPath;//数据库目录
    QString dbName;//数据库名
    QString userName;//用户名
    QString tablePath;//表路径
    int updateColId;//更新字段id


};


#endif //DBMS_MANAGEDATABYSQL_H
