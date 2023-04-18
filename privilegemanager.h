//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_PRIVILEGEMANAGER_H
#define DBMS_PRIVILEGEMANAGER_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class privilegemanager; }
QT_END_NAMESPACE

class privilegemanager : public QWidget {
Q_OBJECT

public:
    explicit privilegemanager(QWidget *parent = nullptr);

    ~privilegemanager() override;

private:
    Ui::privilegemanager *ui;
};


#endif //DBMS_PRIVILEGEMANAGER_H
