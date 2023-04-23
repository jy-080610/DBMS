//
// 创建删除更新表格
//

#ifndef DBMS_TABLEMANAGELOAD_H
#define DBMS_TABLEMANAGELOAD_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class tablemanageload; }
QT_END_NAMESPACE

class tablemanageload : public QWidget {
Q_OBJECT

public:
    explicit tablemanageload(QWidget *parent = nullptr);
    ~tablemanageload() override;
private slots:

    void on_updatetable_clicked();
    void on_deletetable_clicked();
    void on_creattable_clicked();
private:
    Ui::tablemanageload *ui;
};


#endif //DBMS_TABLEMANAGELOAD_H
