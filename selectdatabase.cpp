//
// 选择数据库/选择用户
//


#include "selectdatabase.h"
#include "ui_selectdatabase.h"
#include "qdir.h"
#include"qtextstream.h"
#include"qdebug.h"
#include"qmessagebox.h"
selectdatabase::selectdatabase(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::selectdatabase)
{
    ui->setupUi(this);
}

selectdatabase::~selectdatabase()
{
    delete ui;
}
//打开数据库
void selectdatabase::on_pushButton_clicked() {
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    QString path=dir->path()+"/DBMS/data/sys";
    QFile *file = new QFile(path+ "/curuse.txt");//若文件不存在，则创建文件
    if(!file->open(QIODevice::WriteOnly))
    {QMessageBox::critical(nullptr, "错误", "文件打开失败！");
        return;}

    QTextStream txtOutput(file);
    extern QString name;
    txtOutput <<name<<","<<ui->lineEdit->text();
    txtOutput.flush();//清空缓冲区
    file->close();
    QMessageBox::information(NULL,"提示","选择数据库成功！",QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    qDebug()<<"选择数据库成功";
}
//关闭界面
void selectdatabase::on_pushButton_2_clicked() {

    this->close();
}
