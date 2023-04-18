//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_RESETPASSWORD_H
#define DBMS_RESETPASSWORD_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class resetpassword; }
QT_END_NAMESPACE

class resetpassword : public QWidget {
Q_OBJECT

public:
    explicit resetpassword(QWidget *parent = nullptr);

    ~resetpassword() override;

private:
    Ui::resetpassword *ui;
};


#endif //DBMS_RESETPASSWORD_H
