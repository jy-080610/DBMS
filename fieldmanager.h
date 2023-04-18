//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_FIELDMANAGER_H
#define DBMS_FIELDMANAGER_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class fieldmanager; }
QT_END_NAMESPACE

class fieldmanager : public QWidget {
Q_OBJECT

public:
    explicit fieldmanager(QWidget *parent = nullptr);

    ~fieldmanager() override;

private:
    Ui::fieldmanager *ui;
};


#endif //DBMS_FIELDMANAGER_H
