//
// Created by 52750 on 2023/4/15.
//

#ifndef DBMS_LANDING_H
#define DBMS_LANDING_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class landing; }
QT_END_NAMESPACE

class landing : public QWidget {
Q_OBJECT

public:
    explicit landing(QWidget *parent = nullptr);

    ~landing() override;

//   typedef struct userInformation{
//        QString name;
//        QString password;
//    }userInformation;

signals:
    //登录mainwindow主界面信号
    void login();
    //关闭登录界面信号
    void close_window();
public slots:
    //登录按钮后触发的事件
    void logButton_clicked();
private:
    Ui::landing *ui;
};


#endif //DBMS_LANDING_H
