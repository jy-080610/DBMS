#ifndef LANDING_H
#define LANDING_H
#include "registerw.h"
#include <QWidget>
#include "registerw.h"

extern QString name; // 创建全局变量用户名
namespace Ui {
    class landing;
}

class landing : public QWidget {
Q_OBJECT

public:

    explicit landing(QWidget *parent = nullptr);
    ~landing();

signals:

    void setVisibleSignal();

private slots:

    void on_logButton_clicked();

    void on_registerButton_clicked();

    void on_pushButton_clicked();
    void setVisibleSlot();

signals:

    void setVisibleSignal();
private slots:
    void on_logButton_clicked();
    void on_registerButton_clicked();
    void on_pushButton_clicked();
    void setVisibleSlot();//设置可见
private:

    Ui::landing *ui;
    void getDbList();
    registerw *user_register;
    QStringList dbList;
};

#endif // LANDING_H
