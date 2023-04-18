//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_CREATEDATABASE_H
#define DBMS_CREATEDATABASE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class createdatabase; }
QT_END_NAMESPACE

class createdatabase : public QWidget {
Q_OBJECT

public:
    explicit createdatabase(QWidget *parent = nullptr);

    ~createdatabase() override;

private:
    Ui::createdatabase *ui;
};


#endif //DBMS_CREATEDATABASE_H
