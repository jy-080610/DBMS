//
// Created by YANG on 2023/4/4.
//

#ifndef DBMS_MAINWINDOW_H
#define DBMS_MAINWINDOW_H

#include <QWidget>
#include "landing.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Mainwindow; }
QT_END_NAMESPACE

class Mainwindow : public QWidget {
Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);

    ~Mainwindow() override;

private:
    Ui::Mainwindow *ui;

    //登录界面类的对象作为指针
    landing * m_log;
};


#endif //DBMS_MAINWINDOW_H
