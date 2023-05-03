#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include"dbmanager.h"
#include"tablemanager.h"
#include "managetablebysql.h"
#include"fieldmanager.h"
#include "registerw.h"
#include "dataoperation.h"
#include"createdatabase.h"
int main(int argc, char *argv[]) {
    QApplication::addLibraryPath("C:/Users/Asus/Desktop/DBMS/plugins");
    QApplication a(argc, argv);
    MainWindow w;
    w.show();// 显示窗口
    return QApplication::exec();

}
