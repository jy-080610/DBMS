//
// Created by 52750 on 2023/4/15.
//

#ifndef DBMS_LANDING_H
#define DBMS_LANDING_H

#include <QWidget>
#include <QJsonDocument>
#include <QJsonObject>
#include <QByteArray>
#include<QCheckBox>


QT_BEGIN_NAMESPACE
namespace Ui { class landing; }
QT_END_NAMESPACE

class landing : public QWidget {
Q_OBJECT

public:
    explicit landing(QWidget *parent = nullptr);

    ~landing() override;

    void read_json();//读json
    void write_json();//写json
    void message_init(QString flag1,QString flag2);//根据json内容决定是否填入输入框


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
