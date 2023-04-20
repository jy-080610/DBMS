//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_DELETEDATABASE_H
#define DBMS_DELETEDATABASE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class deletedatabase; }
QT_END_NAMESPACE

class deletedatabase : public QWidget {
Q_OBJECT

public:
    explicit deletedatabase(QWidget *parent = nullptr);

    ~deletedatabase() override;
private slots:

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

private:
    Ui::deletedatabase *ui;
};


#endif //DBMS_DELETEDATABASE_H
