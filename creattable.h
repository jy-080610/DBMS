//
// 创建表
//

#ifndef DBMS_CREATTABLE_H
#define DBMS_CREATTABLE_H

#include <QWidget>
#include "fieldmanager.h"
#include "qmessagebox.h"
#include "qdebug.h"
#include "dbmanager.h"
#include"QDir"
#include "privilegemanager.h"
#include "tablemanager.h"

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
private:
    Ui::creattable *ui;

    void on_add_clicked();

    void on_pushButton_clicked();
};


#endif //DBMS_CREATTABLE_H
