//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_tablemanageload.h" resolved

#include "tablemanageload.h"
#include "ui_tablemanageload.h"
#include "creattable.h"
#include "deletetable.h"
#include "fieldmanager.h"

tablemanageload::tablemanageload(QWidget *parent) :
        QWidget(parent), ui(new Ui::tablemanageload) {
    ui->setupUi(this);
}

tablemanageload::~tablemanageload() {
    delete ui;
}

void tablemanageload::on_updatetable_clicked()
{
    FieldManager *fd = new FieldManager();

    fd->show();
    close();
}

void tablemanageload::on_pushButton_2_clicked()
{
    deletetable *dt = new deletetable();

    dt->show();
    close();
}

void tablemanageload::on_creattable_clicked()
{
    creattable *ct = new creattable();
    ct->show();
    close();
}
