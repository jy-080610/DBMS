//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_DATAOPERATION_H
#define DBMS_DATAOPERATION_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class dataoperation; }
QT_END_NAMESPACE

class dataoperation : public QWidget {
Q_OBJECT

public:
    explicit dataoperation(QWidget *parent = nullptr);

    ~dataoperation() override;

private:
    Ui::dataoperation *ui;
};


#endif //DBMS_DATAOPERATION_H
