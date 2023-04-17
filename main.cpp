#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
#include "table.h"
#include "landing.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();

//    Mainwindow w;
//    w.show();
//    table t;
//    t.show();
    landing l;
    l.show();
    Mainwindow w;
    //这边把主窗口的show()函数注释，这样主窗口才不会自动打开，
    //必须通过登录窗口发出的信号，才能启动主窗口的show()函数。
    //w.show();
    return QApplication::exec();
    //test by fu
    //test
}
