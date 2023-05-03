//
// 删除表
//

// You may need to build the project (run Qt uic code generator) to get "ui_deletetable.h" resolved

#include "deletetable.h"
#include "ui_deletetable.h"
#include "QFileDialog"
#include "qdebug.h"
#include "tablemanager.h"
#include "qmessagebox.h"
#include "privilegemanager.h"

deletetable::deletetable(QWidget *parent) :
        QWidget(parent), ui(new Ui::deletetable) {
    ui->setupUi(this);
}

deletetable::~deletetable() {
    delete ui;
}

void deletetable::on_quitButtton_clicked() {
    this->close();
}


//根据输入的数据库名称删除数据库
void deletetable::on_deleButton_clicked() {
        QDir *dir=new QDir(QDir::currentPath());
        dir->cdUp();//返回上一层目录
       QString dirPath = dir->path() + "/data/sys/curuse.txt";
        QFile file(dirPath);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败";
        }
        QTextStream read(&file);
        QStringList list;
        QString str =read.readLine();

        list=str.split(",");
        file.close();
        //判断用户权限
        privilegemanager deleJudge;
        if(!deleJudge.dtb(this->ui->lineEdit->text(),list[0])){
            QMessageBox::critical(0,"错误","没有权限删除表",QMessageBox::Ok|QMessageBox::Default,QMessageBox::Cancel|QMessageBox::Escape,0);
        }

        //输入的表名不为空且表存在时进行删除
        if(this->ui->lineEdit->text()!=""){
            TableManager TM(list[0],list[1]);
            TM.tableDelete(this->ui->lineEdit->text());//删除表
            QMessageBox::information(0,"提示","表删除成功",QMessageBox::Ok|QMessageBox::Default,QMessageBox::Cancel|QMessageBox::Escape,0);
        }else{
            QMessageBox::critical(0,"错误","表名不能为空",QMessageBox::Ok|QMessageBox::Default,QMessageBox::Cancel|QMessageBox::Escape,0);
        }
        this->ui->lineEdit->clear();
}
