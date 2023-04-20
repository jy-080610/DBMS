//
// Created by lx on 2023/4/5.
//

#ifndef DBMS_ANALYSISSQL_H
#define DBMS_ANALYSISSQL_H
#include "qstringlist.h"

class AnalysisSQL{
public:
    AnalysisSQL();
    QStringList resolveSql(QString sql);
//private:
    //QStringList sqlList;//保存所有可能用到的正则表达式
};


#endif //DBMS_ANALYSISSQL_H
