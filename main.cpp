#include <QApplication>
#include <QPushButton>
#include "mainwindow.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
//    QPushButton button("Hello world!", nullptr);
//    button.resize(200, 100);
//    button.show();
    Mainwindow w;
    w.show();
    return QApplication::exec();
    //test by fu
}
