//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_DATAOPERATION_H
#define DBMS_DATAOPERATION_H

#include <QWidget>
#include <QWidget>
#include <QDialog>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QFileDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class dataoperation; }
QT_END_NAMESPACE

class dataoperation : public QWidget {
Q_OBJECT

public:
    explicit dataoperation(QWidget *parent = nullptr);
    ~dataoperation() override;
    bool isDigitString(const QString& src);//判断是否为数字
    bool isDateString(QString str);//判断是否为日期


    //打开，查看，删除，插入，修改，保存，退出等操作

private slots:
    void on_pushButton_clicked();//打开
    void on_pushButton_insert_clicked();//插入
    void on_pushButton_delete_clicked();//删除
    void on_pushButton_save_clicked();//保存
    void on_pushButton_exit_clicked();//修改

private:
    Ui::dataoperation *ui;
    void initDir();//初始化目录
    void save();//保存
    bool hasSame(QStringList list);//判断是否有重复
    QString dirPath;//数据库目录
    QString dbName;//数据库名
    QString tableNmae;//表名
    QString dataPath;//数据路径
    QVector<QString> x;//QVector是一个模板类，可以存储任意类型的数据
    QVector<QVector<QString>> qv2;
    int col;//列数
    QStringList list1;
    QString filename;
    QString user;
};


#endif //DBMS_DATAOPERATION_H
