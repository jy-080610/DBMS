//
//  2023/4/18.
//

#ifndef DBMS_CREATEDATABASE_H
#define DBMS_CREATEDATABASE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class createdatabase; }
QT_END_NAMESPACE

class createdatabase : public QWidget {
Q_OBJECT

public:
    explicit createdatabase(QWidget *parent = nullptr);

    ~createdatabase() override;
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();
private:
    Ui::createdatabase *ui;
};


#endif //DBMS_CREATEDATABASE_H
