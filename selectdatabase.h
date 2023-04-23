
#ifndef DBMS_SELECTDATABASE_H
#define DBMS_SELECTDATABASE_H
//拟实现数据库各种记录操作，提供一个UI界面，供用户登录,创建用户模式
#include <QWidget>
extern QString dpath;//创建全局变量用户数据库路径
namespace Ui {
    class selectdatabase;
}

class selectdatabase : public QWidget
{
Q_OBJECT

public:
    explicit selectdatabase(QWidget *parent = nullptr);
    ~selectdatabase();

private slots:
    void on_pushButton_clicked();//登录注册按钮

    void on_pushButton_2_clicked();//登录注册按钮

private:
    Ui::selectdatabase *ui;
};

#endif //DBMS_SELECTDATABASE_H
