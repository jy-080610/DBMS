//
// Created by 52750 on 2023/4/15.
//

#ifndef DBMS_LANDING_H
#define DBMS_LANDING_H

#include <QWidget>
#include "registerw.h"

extern QString name; // 创建全局变量用户名

QT_BEGIN_NAMESPACE
namespace Ui { class landing; }
QT_END_NAMESPACE

class landing : public QWidget {
Q_OBJECT

public:
    explicit landing(QWidget *parent = nullptr);

    ~landing() override;

signals:

    void setVisibleSignal();
private slots:
    void on_logButton_clicked();
    void on_registerButton_clicked();
    void on_pushButton_clicked();
    void setVisibleSlot();
private:

    Ui::landing *ui;
    void getDbList();
    registerw *user_register;
    QStringList dbList;
};


#endif //DBMS_LANDING_H
