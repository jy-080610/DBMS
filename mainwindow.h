//
// Created by YANG on 2023/4/4.
//

#ifndef DBMS_MAINWINDOW_H
#define DBMS_MAINWINDOW_H

#include <QWidget>
#include "landing.h"
#include "privilegemanager.h"
#include "indexmanager.h"
#include "qdebug.h"
#include "managetablebysql.h"
#include "managedatabysql.h"
#include "managefieldbysql.h"
#include "dbmanager.h"
#include "qmessagebox.h"
#include "qfiledialog.h"
#include"analysissql.h"
#include "qdirmodel.h"
#include"fieldmanager.h"
#include"dataoperation.h"
#include"tablemanageload.h"
#include"createdatabase.h"
#include"deletedatabase.h"

QT_BEGIN_NAMESPACE
namespace Ui { class Mainwindow; }
QT_END_NAMESPACE

class Mainwindow : public QWidget {
Q_OBJECT

public:
    explicit Mainwindow(QWidget *parent = nullptr);

    ~Mainwindow() override;
private slots:
    void setVisibleSlot();

    void on_run_clicked();
    void on_fieldmanage_clicked();
    void on_datamanage_clicked();
    void on_tablemanage_clicked();

    void on_create_clicked();

    void on_del_clicked();
private:
    Ui::Mainwindow *ui;
    AnalysisSQL *dealwithSql;
    QString dirPath;
    QString dbname;
    void    displayField(QString);
    void    displayDir();
    //登录界面类的对象作为指针
    //landing * m_log;

};


#endif //DBMS_MAINWINDOW_H
