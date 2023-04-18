//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_dataoperation.h" resolved

#include "dataoperation.h"
#include "ui_dataoperation.h"


dataoperation::dataoperation(QWidget *parent) :
        QWidget(parent), ui(new Ui::dataoperation) {
    ui->setupUi(this);
}

dataoperation::~dataoperation() {
    delete ui;
}
