//
// Created by Asus on 2023/4/18.
//

#ifndef DBMS_CREATTABLE_H
#define DBMS_CREATTABLE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class creattable; }
QT_END_NAMESPACE

class creattable : public QWidget {
Q_OBJECT

public:
    explicit creattable(QWidget *parent = nullptr);

    ~creattable() override;

private:
    Ui::creattable *ui;
};


#endif //DBMS_CREATTABLE_H