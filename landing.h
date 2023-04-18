//
// Created by 52750 on 2023/4/15.
//

#ifndef DBMS_LANDING_H
#define DBMS_LANDING_H

#include <QWidget>
extern QString name; // 创建全局变量用户名

QT_BEGIN_NAMESPACE
namespace Ui { class landing; }
QT_END_NAMESPACE

class landing : public QWidget {
Q_OBJECT

public:
    explicit landing(QWidget *parent = nullptr);

    ~landing() override;

private:
    Ui::landing *ui;
};


#endif //DBMS_LANDING_H
