#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include"dbmanager.h"
#include"tablemanager.h"
#include"fieldmanager.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
//    landing l;
//    l.show();
    Mainwindow w;
    //dbmanager db;
    //db.myCreateDataBase("test");
    //db.myDeteleDataBase("test");
    QDir *dir = new QDir(QDir::currentPath());//获取当前路径
    dir->cdUp();//返回上一级目录
    QString path =dir->path()+"/data/sys";//系统文件路径
    QDir dir1(path);//创建QDir对象
    if(!dir1.exists()){//判断系统文件夹是否存在
        dir1.mkdir(path);//创建系统文件夹
    }

    QString path1 =dir->path()+"/data/log";//日志文件路径
    QDir dir2(path);//创建QDir对象
    if(!dir2.exists()){//判断日志文件夹是否存在
        dir2.mkdir(path);//创建日志文件夹
    }

    //FieldManager fm;
    //fm.show();



    //TableManager tb("wende","test");
    //tb.tableCreator("table1");

    //这边把主窗口的show()函数注释，这样主窗口才不会自动打开，
    //必须通过登录窗口发出的信号，才能启动主窗口的show()函数。
    w.show();
    return QApplication::exec();
    //test by fu
    //test
}
