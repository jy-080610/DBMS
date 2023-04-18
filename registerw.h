//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_REGISTERW_H
#define DBMS_REGISTERW_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class registerw; }
QT_END_NAMESPACE

class registerw : public QWidget {
Q_OBJECT

public:
    explicit registerw(QWidget *parent = nullptr);

    ~registerw() override;
signals:

    //void setVisibleSignal();

private slots:


    void createuser(QString name);

private:
    Ui::registerw *ui;
};


#endif //DBMS_REGISTERW_H
