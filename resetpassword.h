//
// 重设密码
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
private slots:
    void on_modifyButton_clicked();

    void on_exitButton_clicked();

private:
    Ui::resetpassword *ui;
    QString path;

    bool checkLog(QString,QString,QString);
    void getDbList();
};


#endif //DBMS_RESETPASSWORD_H
