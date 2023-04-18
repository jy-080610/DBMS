//
// Created by YANG on 2023/4/18.
//

#ifndef DBMS_DBMANAGER_H
#define DBMS_DBMANAGER_H
#include<QString>
#include"qdatetime.h"
//#include"selectdatabase.h"
using namespace std;
typedef struct dataBase{
    char daname[128];
    bool type;
    char filename[256];
    QDateTime crtime;
}database;
class dbmanager
{
public:
    dbmanager();

    void myCreateDataBase(QString dataname);
    void myDeteleDataBase(QString dataname);
    void writeDBinto(struct dataBase my_database);
    void writedelDBinto(QString dataname);
//private:
    QString path;
    QString dataPath;
};
#endif //DBMS_DBMANAGER_H
