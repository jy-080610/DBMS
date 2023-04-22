//
// 管理字段
//

#ifndef DBMS_MANAGEFIELDBYSQL_H
#define DBMS_MANAGEFIELDBYSQL_H

#include "qstringlist.h"
#include "qstring.h"
class managefieldbysql {
public:
    managefieldbysql();//构造函数
    void  addField2tdf(QStringList);
    void deleFileFromtdf(QStringList);
    void modifyInfo2tb(QStringList);
private:
    void initDir();//   初始化目录
    bool isDuplicate(QStringList);//判断是否有重复的属性名
    void addComma2trd(QStringList);//添加字段后调用此函数保证字段和数据的列数相同
    void removedata(int,QString);//删除某行数据
    QString dirPath;
    QString dbName;
    QString userName;
    QString tablePath;


};


#endif //DBMS_MANAGEFIELDBYSQL_H
