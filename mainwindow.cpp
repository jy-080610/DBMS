//
// Created by YANG on 2023/4/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_Mainwindow.h"


Mainwindow::Mainwindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::Mainwindow) {
    ui->setupUi(this);

    //通过指针创建登录界面类的对象
    m_log= new landing;
    //调用登录窗口的show()函数显示界面
    m_log->show();

    //建立信号槽，到接受到登录界面发来的login信号后，调用主窗口的show（）函数
    connect(m_log, SIGNAL(login()),this, SLOT(show()));
}

Mainwindow::~Mainwindow() {
    delete ui;
}
