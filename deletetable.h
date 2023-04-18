//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_DELETETABLE_H
#define DBMS_DELETETABLE_H

#include <QWidget>


QT_BEGIN_NAMESPACE
namespace Ui { class deletetable; }
QT_END_NAMESPACE

class deletetable : public QWidget {
Q_OBJECT

public:
    explicit deletetable(QWidget *parent = nullptr);

    ~deletetable() override;

private:
    Ui::deletetable *ui;
};


#endif //DBMS_DELETETABLE_H
