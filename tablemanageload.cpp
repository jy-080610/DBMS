//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_tablemanageload.h" resolved

#include "tablemanageload.h"
#include "ui_tablemanageload.h"
#include "fieldmanager.h"
#include "creattable.h"
#include "deletetable.h"

tablemanageload::tablemanageload(QWidget *parent) :
        QWidget(parent), ui(new Ui::tablemanageload) {
    ui->setupUi(this);
}

tablemanageload::~tablemanageload() {
    delete ui;
}

void tablemanageload::on_updatetable_clicked() {
  fieldmanager *fieldmanager1 = new fieldmanager();
  fieldmanager1->show();
  close();
}

void tablemanageload::on_deletetable_clicked() {
    deletetable *deletetable1 = new deletetable();
    deletetable1->show();
    close();
}

void tablemanageload::on_creattable_clicked() {
    creattable *creattable1 = new creattable();
    creattable1->show();
    close();
}
