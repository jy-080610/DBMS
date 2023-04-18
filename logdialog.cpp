//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_logdialog.h" resolved

#include "logdialog.h"
#include "ui_logdialog.h"
#include"qdir.h"
#include"qtextstream.h"//文本流
#include"qdebug.h"



logdialog::logdialog(QWidget *parent) :
        QDialog(parent), ui(new Ui::logdialog) {
    ui->setupUi(this);
}

logdialog::~logdialog() {
    delete ui;
}

void logdialog::showlog() {
    QDir * dir = new QDir(QDir::currentPath());//获取当前路径
    dir->cdUp();//返回上一级目录
    QString path = dir->path() + "/DBMS/log/sys.txt";//获取日志文件路径
    QFile file(path);
    if(!file.open(QIODevice::ReadWrite))return;
    QTextStream out(&file);//文本流
    while(!file.atEnd())//读取文件
    {
        ui->textEdit->setText(out.readAll());//显示日志
    }
    qDebug()<<"打开日志，显示日志成功";

}

void logdialog::on_pushButton_clicked() {
      close();//关闭日志窗口
}
