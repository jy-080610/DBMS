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


private slots:

    //更新表
    void on_updatetable_clicked();
    //删除表
    void on_pushButton_2_clicked();
    //创建表
    void on_creattable_clicked();

private:
    Ui::tablemanageload *ui;
};




#endif //DBMS_TABLEMANAGELOAD_H
