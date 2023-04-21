//
//建表操作
//

// You may need to build the project (run Qt uic code generator) to get "ui_creattable.h" resolved

#include "creattable.h"
#include "ui_creattable.h"
#include "tablemanager.h"
#include "qmessagebox.h"
#include "privilegemanager.h"
#include "fieldmanager.h"
//创建表，写入文件并记录

creattable::creattable(QWidget *parent) :
        QWidget(parent), ui(new Ui::creattable) {
    ui->setupUi(this);
}
//为表添加属性
void creattable::on_add_clicked() {
    fieldmanager * fd= new fieldmanager();//创建属性管理界面
    fd->show();//显示属性管理界面
    close();//关闭当前界面
}
//根据用户输入的表名创建表
void creattable::on_pushButton_clicked() {

    QDir *dir=new QDir(QDir::currentPath());//获取当前路径
    dir->cdUp();//返回上一级目录
    QString dirPath=dir->path()+"/DBMS/data/sys/curuse.txt";//获取当前使用的数据库


    QFile file(dirPath);//打开当前使用的数据库
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return;
    }
    QTextStream read(&file);//读取文件
    QStringList list;//创建字符串列表
    QString str=read.readLine();//读取一行
    //list中依次存储着当前使用的数据库的用户名，数据库名
    list=str.split(",");
    file.close();//关闭文件
    privilegemanager createJudge;//创建权限管理对象,判断用户有无对表的操作权限
    if(!createJudge.ctb((this->ui->lineEdit->text()),list[0]))//判断用户有无对表的操作权限
    {
        QMessageBox::critical(0,"错误","您没有对该表的操作权限",
                              QMessageBox::Ok|QMessageBox::Default,
                              QMessageBox::Cancel|QMessageBox::Escape,0);
        return;
    }
    //创建表
    //若表名输入不为空则创建表文件
    if (this->ui->lineEdit->text()!=""){
        TableManager TM(list[0],list[1]);//创建表管理对象
        TM.tableCreator(this->ui->lineEdit->text());//创建表
        QMessageBox::information(0,"提示","表创建成功",
                                 QMessageBox::Ok|QMessageBox::Default,
                                 QMessageBox::Cancel|QMessageBox::Escape,0);

    }else{
        QMessageBox::critical(0,"错误","表名不能为空",
                              QMessageBox::Ok|QMessageBox::Default,
                              QMessageBox::Cancel|QMessageBox::Escape,0);
    }
    //清空输入框
    this->ui->lineEdit->clear();
}

creattable::~creattable() {
    delete ui;
}

void creattable::on_add_clicked() {
    FieldManager *fd = new FieldManager();
    fd->show();
    close();
}

void creattable::on_pushButton_clicked() {
// 初始化用户目录，读取当前的用户和所使用的数据库
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString dirPath = dir->path() + "/data/sys/curuse.txt";

    // 以只读方式打开信息文件
    QFile file(dirPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    // list中依次存储着用户名和数据库名
    list = str.split(",");
    file.close();
    // 首先进行用户权限判断
    privilegemanager createJudge;

    if (!createJudge.ctb(this->ui->lineEdit->text(), list[0])) {
        QMessageBox::critical(nullptr, "错误", "无创建表权限",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    // 若表名输入不为空，则进行创建
    if (this->ui->lineEdit->text() != "") {
        // 根据传入的用户名和数据库名，在相应位置创建表文件
        TableManager TM(list[0], list[1]);
        TM.tableCreator(this->ui->lineEdit->text());

        // 成功提示信息
        QMessageBox::information(nullptr,
                                 "通知",
                                 "创建成功",
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::Cancel | QMessageBox::Escape, 0);
    } else {
        // 失败提示信息
        QMessageBox::critical(nullptr, "错误", "请输入表名",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
    this->ui->lineEdit->clear();
}
