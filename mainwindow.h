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
private slots:
    void setVisibleSlot();
private:
    Ui::Mainwindow *ui;

};


#endif //DBMS_MAINWINDOW_H
