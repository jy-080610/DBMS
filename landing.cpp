//
// 登陆管理
//
#include <QDir>
#include <QMessageBox>
#include "landing.h"
#include "ui_landing.h"

#include "login.h"
#include "QDebug"
#include "mainwindow.h"
QString name = "DBMS"; // 初始化全局变量
landing::landing(QWidget *parent) :
        QWidget(parent), ui(new Ui::landing) {
    ui->setupUi(this);
    // 去窗口边框
   // setWindowFlags(Qt::FramelessWindowHint | windowFlags());
    // 把窗口背景设置为透明;
//      setAttribute(Qt::WA_TranslucentBackground);
    // 建立注册界面与登陆界面的信道槽
    user_register = new registerw();
    user_register->hide();
    connect(user_register, SIGNAL(setVisibleSignal()), this,
            SLOT(setVisibleSlot()));
    // 获取目录下存在的数据库名称
    getDbList();
    this->show();

}

landing::~landing() {
    delete ui;
}

void landing::on_logButton_clicked() {
// 当用户名和密码都输入后，进行如下操作
    if ((ui->userName->text() != "") && (ui->passWord->text() != "")) {
        login l;

        // 检查登陆是否成功，成功后切换到主界面
        if (l.checkLog(ui->dbName->currentText(), ui->userName->text(),
                       ui->passWord->text())) {
            qDebug() << "成功";
            name = ui->userName->text();
            this->hide();
            // 向主界面发射信号，显示主界面
            emit setVisibleSignal();
            ui->userName->clear();
            ui->passWord->clear();
        } else {
            qDebug() << "出错";
        }
    }
}
// 切换到注册界面
void landing::on_registerButton_clicked() {
// 切换到注册界面
    user_register->show();
    this->hide();// 隐藏登陆界面
}

void landing::on_pushButton_clicked() {
    exit(0);
}

void landing::setVisibleSlot() {
    this->show();
}

void landing::getDbList() {
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();

    // --1 判断文件夹是否存在
    QString folderPath = dir->path() + "/data";
    QDir    dbDir(folderPath);

    if (!dbDir.exists())
    {
        QMessageBox::critical(this, tr("错误"), tr("数据库文件夹不存在"));
        return;
    }

    // --2 获取当前路径下所有的文件夹名字
    // -- 注：QDir::Dirs 为获取所有文件夹名称，获取文件名称需要修改
    QStringList names = dbDir.entryList(QDir::Dirs);

    // --3 删除当前文件夹和上级文件夹（温馨提示：隐藏的文件夹获取不了）
    names.removeOne(".");
    names.removeOne("..");
    names.removeOne("sys");
    // --4 打印出获取的文件名
    qDebug() << "names: " << names;

     for (int i = 0; i < names.size(); i++) {
        ui->dbName->addItem(names[i]);
    }
}
