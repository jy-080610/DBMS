//
// 创建表
//

#ifndef DBMS_CREATTABLE_H
#define DBMS_CREATTABLE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class creattable; }
QT_END_NAMESPACE

class creattable : public QWidget {
Q_OBJECT

public:
    explicit creattable(QWidget *parent = nullptr);

    ~creattable() override;

private slots:
    void on_add_clicked();

    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
private:
    Ui::creattable *ui;
};


#endif //DBMS_CREATTABLE_H
