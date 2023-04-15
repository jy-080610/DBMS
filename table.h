//
// Created by 52750 on 2023/4/15.
//

#ifndef DBMS_TABLE_H
#define DBMS_TABLE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class table; }
QT_END_NAMESPACE

class table : public QWidget {
Q_OBJECT

public:
    explicit table(QWidget *parent = nullptr);

    ~table() override;

private:
    Ui::table *ui;
};


#endif //DBMS_TABLE_H
