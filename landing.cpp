//
// 登陆管理
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

    //读取read_json文件
    read_json();
}

landing::~landing() {
    delete ui;
}

void landing::read_json()
{
    //打开文件
    QFile file(QApplication::applicationDirPath()+"/config.json");
    if(!file.open(QIODevice::ReadOnly)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() <<"File open successfully!";
    }
    QJsonDocument jdc(QJsonDocument::fromJson(file.readAll()));
    QJsonObject obj = jdc.object();
    QString save_name_flag=obj.value("SAVE_NAME").toString();
    QString save_password_flag=obj.value("SAVE_PASSWORD").toString();
    message_init(save_name_flag,save_password_flag);
}

void landing::message_init(QString flag1,QString flag2)
{
    if (flag1 == "1")
    {
        ui->userName->setText("FuYunxiang");
        ui->checkBox->setChecked(true);
    }
    if(flag2 == "1")
    {
        ui->passWord->setText("123456");
        ui->checkBox_2->setChecked(true);
    }

}

void landing::logButton_clicked() {
    //从输入框获取账号
    QString name =ui->userName->text();
    //从输入框获取密码
    QString password=ui->passWord->text();

//    //userInformation example;
//    QFile file("./user.txt");
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


    if(name=="FuYunxiang" && password=="123456")
    {
        //发出登录信号
        emit(login());

        write_json();


        //发出关闭窗口信号
        emit(close_window());
    }
    else//账号或者密码错误
        QMessageBox::information(this, "Warning","Username or Password is wrong !");

}

void landing::write_json()
{
    QFile file(QApplication::applicationDirPath()+"/config.json");
    if(!file.open(QIODevice::WriteOnly)) {
        qDebug() << "File open failed!";
    } else {
        qDebug() <<"File open successfully!";
    }
    QJsonObject obj;
    bool flag = ui->checkBox->isChecked();
    if(flag == true)
    {
        obj["SAVE_NAME"] = "1";
    }
    else
        obj["SAVE_NAME"] = "0";
    flag = ui->checkBox_2->isChecked();
    if(flag == true)
    {
        obj["SAVE_PASSWORD"] = "1";
    }
    else
        obj["SAVE_PASSWORD"] = "0";
    QJsonDocument jdoc(obj);
    file.write(jdoc.toJson());
    file.flush();
}
