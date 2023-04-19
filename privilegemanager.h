//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_PRIVILEGEMANAGER_H
#define DBMS_PRIVILEGEMANAGER_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class privilegemanager; }
QT_END_NAMESPACE

class privilegemanager : public QWidget {
Q_OBJECT

public:
    explicit privilegemanager(QWidget *parent = nullptr);

    ~privilegemanager() override;
    //返回用户对表的操作权限
    bool ctb(QString,QString);//创建表
    bool dtb(QString,QString);//删除表
    bool adt(QString,QString);//添加数据
    bool ddt(QString,QString);//删除数据
    bool mdt(QString,QString);//修改数据

    //授权与回收权限
    void grant(QStringList);//授权
    void revoke(QStringList);//回收权限

private slots:
    void on_querry_clicked();//返回
    void on_finish_clicked();//完成
    void on_exit_clicked();//退出

private:
    Ui::privilegemanager *ui;
    void initDir();//初始化目录
    void display();//显示权限
    bool isfuserexist(QString,QString);
    bool isuserexist(QString);
    void initPrivilege(QString,QString);//初始化权限


    QString dirPath;//用户目录
    QString dbName;//数据库名
    QString userName;//用户名
    QString privilegePath;//权限文件路径
    QString tablePath;//表文件路径
    QString tPath;//表目录路径
};


#endif //DBMS_PRIVILEGEMANAGER_H
