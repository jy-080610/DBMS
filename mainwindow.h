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
#include"managetablebysql.h"

#include <QStandardItemModel>
#include "landing.h"
#include <QMainWindow>
#include "selectdatabase.h"
#include <QPainter>
#include <QPixmap>
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

    void on_run_clicked();//运行
    void on_rollback_clicked();//回滚
    void on_commit_clicked();//提交

    void on_fieldmanage_clicked();//字段管理
    void on_datamanage_clicked();//数据管理
    void on_tablemanage_clicked();//表管理
    void on_log_clicked();//日志
    void on_privilege_clicked();//权限管理
    void on_rland_clicked();//重新登陆
    void on_psw_clicked();//修改密码
    void on_exit_clicked();//退出
    void on_selectAction_clicked();//选择
    void on_deleteAction_clicked();//删除
    void on_newAction_clicked();//新建

private:
    Ui::MainWindow *ui;
    QStandardItemModel *model;
    landing *l;
    AnalysisSQL *dealwithSql;
    QString dirPath;
    QString dbname;


    void        displayField(QString);//显示字段
    void        displayData(QString);
    void        displayDir();
    void        importScript(QString);
    void        parseSql(QString);
    void        selectData(QStringList);
    bool        selectByIndex(QStringList);
    bool        bakeupFile();
    bool        isLogExists();
    QStringList gettablelist();
};


#endif //DBMS_MAINWINDOW_H
