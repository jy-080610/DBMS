//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_TABLEMANAGER_H
#define DBMS_TABLEMANAGER_H

#include "qstring.h"
#include "qdebug.h"
#include "qdir.h"
class TableManager {
public:

    TableManager();
    TableManager(QString,QString);
    bool isTableExist(QString);
    void tableCreator(QString);
    void tableModifier(QString,int);
    bool tableDelete(QString);

private:

    QString dirPath;
    QString tablePath;
    QString username;
};

#endif //DBMS_TABLEMANAGER_H
