//
//  注册创建数据库用户
//


#include "registerw.h"
#include "ui_registerw.h"
#include "login.h"
#include "QDebug"
#include "qdir.h"
#include "qmessagebox.h"
registerw::registerw(QWidget *parent) :
        QWidget(parent), ui(new Ui::registerw) {
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);//设置窗口背景透明
    getDbList();//获取数据库列表
}

registerw::~registerw() {
    delete ui;
}

//创建用户目录
void registerw::createuser(QString name) {
    QDir   *dir = new QDir(QDir::currentPath());
    QString path;
    dir->cdUp();
    path = dir->path() + "/DBMS/data/" + name;
    QDir dir1(path);
    // 若当前目录存在，则创建失败；否则创建新目录
    if (dir1.exists()) {
        qDebug() << "数据库用户创建失败";
        return;
    } else {
        dir1.mkdir(path);
        qDebug() << "数据库用户创建成功";
        return;
    }
}

void registerw::on_registerButton_clicked() {
    login l;
    // 如果输入的用户名密码正确，则将信息保存到文件中
    if (l.checkError(ui->dbName->currentText(), ui->username->text(),ui->psw1->text(),ui->psw2->text()) == 0) {
        l.insert2File(ui->dbName->currentText(),
                      ui->username->text(),
                      ui->psw1->text());

        // createuser(ui->lineEdit->text());

        emit setVisibleSignal();
        QMessageBox::information(0,
                                 "通知",
                                 "注册成功",
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::Cancel | QMessageBox::Escape, 0);
        close();
    } else {
        QMessageBox::critical(this, tr("错误"), tr("注册失败"));
    }
}

void registerw::on_quitButton_clicked() {
    this->hide();
    emit setVisibleSignal();
    // 清空文本框内容
    ui->username->clear();
    ui->psw1->clear();
    ui->psw2->clear();
}
//返回数据库文件夹下的所有数据库
void registerw::getDbList() {
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    //获取数据库文件夹路径
    QString folderPath = dir->path() + "/DBMS/data";
    QDir dbDir(folderPath);
    if (!dbDir.exists()) {
        qDebug() << "数据库文件夹不存在";
        QMessageBox::critical(0, "错误", "数据库文件夹不存在",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    //获取数据库文件夹下的所有数据库
    QStringList names = dbDir.entryList(QDir::Dirs );
    //去除"."和".."两个目录
    names.removeOne(".");//去除"."
    names.removeOne("..");//去除".."
    names.removeOne("sys");//去除"sys"

    //将数据库名添加到下拉框中
    for (int i = 0; i < names.size(); i++) {
        ui->dbName->addItem(names[i]);
    }

}
