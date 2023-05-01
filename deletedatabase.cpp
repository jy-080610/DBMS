//
// 删除数据库文件
//

// You may need to build the project (run Qt uic code generator) to get "ui_deletedatabase.h" resolved

#include "deletedatabase.h"
#include "dbmanager.h"
#include "ui_deletedatabase.h"


deletedatabase::deletedatabase(QWidget *parent) :
        QWidget(parent), ui(new Ui::deletedatabase) {
    ui->setupUi(this);
}

deletedatabase::~deletedatabase() {
    delete ui;
}

void deletedatabase::on_pushButton_clicked() {
    QString str=ui->lineEdit->text();
    dbmanager *userdata=new dbmanager();
    userdata->myDeteleDataBase(str);
}

void deletedatabase::on_pushButton_2_clicked() {
        close();
}

void deletedatabase::on_pushButton_3_clicked() {
  //关闭当前窗口
  this->close();
}

