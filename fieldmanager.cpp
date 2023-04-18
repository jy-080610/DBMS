//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_fieldmanager.h" resolved

#include "fieldmanager.h"
#include "ui_fieldmanager.h"


fieldmanager::fieldmanager(QWidget *parent) :
        QWidget(parent), ui(new Ui::fieldmanager) {
    ui->setupUi(this);
}

fieldmanager::~fieldmanager() {
    delete ui;
}
