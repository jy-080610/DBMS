//
// 属性管理-主键，非空，NULL值，数据类型
//

#ifndef DBMS_FIELDMANAGER_H
#define DBMS_FIELDMANAGER_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class fieldmanager; }
QT_END_NAMESPACE

class fieldmanager : public QWidget {
Q_OBJECT

public:
    explicit fieldmanager(QWidget *parent = nullptr);

    ~fieldmanager() override;


private slots:
    void on_add_clicked();
    void on_modify_clicked();
    void on_dele_clicked();
    void on_display_clicked();
    void on_isPK_clicked();
    void on_isNull_clicked();

private:
    Ui::fieldmanager *ui;
    void initDir();
    bool isTableExist();
    QString dirPath;
    QString dbName;
    QString userName;
    QString tablePath;
    void display();
    bool isDuplicate(QString);//判断是否有重复的属性名
    void addComma2trd();
    void removedata(int);
};


#endif //DBMS_FIELDMANAGER_H
