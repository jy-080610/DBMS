//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_tablemanageload.h" resolved

#include "tablemanageload.h"
#include "ui_tablemanageload.h"


tablemanageload::tablemanageload(QWidget *parent) :
        QWidget(parent), ui(new Ui::tablemanageload) {
    ui->setupUi(this);
}

tablemanageload::~tablemanageload() {
    delete ui;
}
