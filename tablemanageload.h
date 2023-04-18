//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_TABLEMANAGELOAD_H
#define DBMS_TABLEMANAGELOAD_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class tablemanageload; }
QT_END_NAMESPACE

class tablemanageload : public QWidget {
Q_OBJECT

public:
    explicit tablemanageload(QWidget *parent = nullptr);

    ~tablemanageload() override;

private:
    Ui::tablemanageload *ui;
};


#endif //DBMS_TABLEMANAGELOAD_H
