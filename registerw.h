//
// 注册创建数据库用户
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

    void setVisibleSignal();

private slots:
    void on_registerButton_clicked();
    void on_quitButton_clicked();
    void createuser(QString name);

private:
    Ui::registerw *ui;
    void getDbList();
};


#endif //DBMS_REGISTERW_H
