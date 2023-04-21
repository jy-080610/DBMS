//
//建表操作
//

// You may need to build the project (run Qt uic code generator) to get "ui_creattable.h" resolved

#include "creattable.h"
#include "ui_creattable.h"


creattable::creattable(QWidget *parent) :
        QWidget(parent), ui(new Ui::creattable) {
    ui->setupUi(this);
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
