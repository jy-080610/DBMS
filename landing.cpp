//
// Created by 52750 on 2023/4/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_landing.h" resolved

#include "landing.h"
#include "ui_landing.h"
#include<QMessageBox>
#include <QFile>
#include <QTextStream>
#include <qdebug.h>


landing::landing(QWidget *parent) :
        QWidget(parent), ui(new Ui::landing) {
    ui->setupUi(this);

    //connect 信号槽

    //触发登录按钮的信号槽连接
    connect(ui->logButton,SIGNAL(clicked(bool)),this,SLOT(logButton_clicked()));

    //发出信号后关闭登录窗口的信号槽连接
    connect(this, SIGNAL(close_window()),this,SLOT(close()));

    //输入密码的时候显示圆点
    ui->passWord->setEchoMode(QLineEdit::Password);
}

landing::~landing() {
    delete ui;
}

void landing::logButton_clicked() {
    //从输入框获取账号
    QString name =ui->userName->text();
    //从输入框获取密码
    QString password=ui->passWord->text();

//    //userInformation example;
//    QFile file("./userInformation");
//    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
//    {
//        QString line1;
//        QString line2;
//        QTextStream in(&file);
//        line1=in.readLine();
//        line2=in.readLine();
//        qDebug()<<line1<<" "<<line2;
//        if( QString::compare(name,line1)==0 && QString::compare(password,line2)==0 )
//        {
//        //发出登录信号
//        emit(login());
//        //发出关闭窗口信号
//        emit(close_window());
//        }
//        else//账号或者密码错误
//            QMessageBox::information(this, "Warning","Username or Password is wrong !");
//    }


    if(name=="FuYunxaing" && password=="123456")
    {
        //发出登录信号
        emit(login());
        //发出关闭窗口信号
        emit(close_window());
    }
    else//账号或者密码错误
        QMessageBox::information(this, "Warning","Username or Password is wrong !");


}
