#include "registerw.h"
#include "ui_registerw.h"
#include "login.h"
#include "QDebug"
#include "qdir.h"
#include "qmessagebox.h"
registerw::registerw(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::registerw)
{
    ui->setupUi(this);

    // 去窗口边框
    //setWindowFlags(Qt::FramelessWindowHint | windowFlags());

    // 把窗口背景设置为透明;
    //setAttribute(Qt::WA_TranslucentBackground);

    // 设置数据库目录列表
    getDbList();
}

registerw::~registerw()
{
    delete ui;
}

// 返回数据库文件夹的目录
void registerw::getDbList()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();

    // --1 判断文件夹是否存在
    QString folderPath = dir->path() + "/data";
    qDebug()<<folderPath;
    QDir    dbDir(folderPath);

    if (!dbDir.exists())
    {
        QMessageBox::critical(this, tr("错误"), tr("文件夹找不到"));
        return;
    }

    // --2 获取当前路径下所有的文件夹名字
    // -- 注：QDir::Dirs 为获取所有文件夹名称，获取文件名称需要修改
    QStringList names = dbDir.entryList(QDir::Dirs);

    // --3 删除当前文件夹和上级文件夹（温馨提示：隐藏的文件夹获取不了）
    names.removeOne(".");
    names.removeOne("..");
    names.removeOne("sys");

    // --4 将数据库名称添加到组件中
    for (int i = 0; i < names.size(); i++) {
        ui->dbName->addItem(names[i]);
        qDebug()<<"已添加";
    }

}

/*
 * @Brief:  注册按钮
 * @Return: NULL
 */
void registerw::on_registerButton_clicked()
{
    login l;

    // 如果输入的用户名密码无响应错误，则将信息保存到文件中
    if (l.checkError(ui->dbName->currentText(), ui->username->text(),
                     ui->psw1->text(),
                     ui->psw2->text()) == 0) {
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

/*
 * @Brief:  退出按钮
 * @Return: NULL
 */
void registerw::on_quitButton_clicked()
{
    this->hide();
    emit setVisibleSignal();

    // 清空文本框内容
    ui->username->clear();
    ui->psw1->clear();
    ui->psw2->clear();
}

/*
 * @Brief:  创建用户目录
 * @Param:  name 用户名t
 * @Return: NULL
 */
void registerw::createuser(QString name) {
    // 初始化系统目录
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
