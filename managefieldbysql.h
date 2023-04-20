//
// Created by Asus on 2023/4/17.
//
#ifndef MANAGEFIELDBYSQL_H
#define MANAGEFIELDBYSQL_H
#include "qstringlist.h"

class ManageFieldBySql {
public:

    ManageFieldBySql();
    void addField2tdf(QStringList);
    void deleFileFromtdf(QStringList);
    void modifyInfo2tb(QStringList);

private:

    void initDir();

    bool isDuplicate(QStringList);
    void addComma2trd(QStringList);
    void removedata(int,
                    QString);

    QString dirPath;
    QString dbName;
    QString userName;
    QString tablePath;
};

#endif // MANAGEFIELDBYSQL_H
