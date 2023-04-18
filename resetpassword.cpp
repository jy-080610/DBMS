//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_resetpassword.h" resolved

#include "resetpassword.h"
#include "ui_resetpassword.h"


resetpassword::resetpassword(QWidget *parent) :
        QWidget(parent), ui(new Ui::resetpassword) {
    ui->setupUi(this);
}

resetpassword::~resetpassword() {
    delete ui;
}
