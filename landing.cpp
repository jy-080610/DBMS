//
// Created by 52750 on 2023/4/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_landing.h" resolved

#include "landing.h"
#include "ui_landing.h"


landing::landing(QWidget *parent) :
        QWidget(parent), ui(new Ui::landing) {
    ui->setupUi(this);
}

landing::~landing() {
    delete ui;
}
