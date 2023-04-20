//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_MANAGETABLEBYSQL_H
#define DBMS_MANAGETABLEBYSQL_H

#include "QString"
class ManageTableBySql {
public:

    ManageTableBySql();
    void createTable(QString);
    void deleteTable(QString);
};

#endif // MANAGETABLEBYSQL_H