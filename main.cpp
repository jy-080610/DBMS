#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include"dbmanager.h"
#include"tablemanager.h"
#include "managetablebysql.h"
#include"fieldmanager.h"
#include "registerw.h"
#include"createdatabase.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    Mainwindow w;
    //dbmanager db;
    //db.myCreateDataBase("test");
    //db.myDeteleDataBase("test");

    w.show();
    return QApplication::exec();
    //test by fu
    //test
}
