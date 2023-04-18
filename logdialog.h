//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_LOGDIALOG_H
#define DBMS_LOGDIALOG_H

#include <QDialog>


QT_BEGIN_NAMESPACE
namespace Ui { class logdialog; }
QT_END_NAMESPACE

class logdialog : public QDialog {
Q_OBJECT

public:
    explicit logdialog(QWidget *parent = nullptr);

    ~logdialog() override;//析构函数
    void showlog();//显示日志

private slots:
    void on_pushButton_clicked();//退出按钮

private:
    Ui::logdialog *ui;
};


#endif //DBMS_LOGDIALOG_H
