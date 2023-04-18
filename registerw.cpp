//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_registerw.h" resolved

#include "registerw.h"
#include "ui_registerw.h"


registerw::registerw(QWidget *parent) :
        QWidget(parent), ui(new Ui::registerw) {
    ui->setupUi(this);
}

registerw::~registerw() {
    delete ui;
}
