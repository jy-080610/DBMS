//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_createdatabase.h" resolved

#include "createdatabase.h"
#include "ui_createdatabase.h"


createdatabase::createdatabase(QWidget *parent) :
        QWidget(parent), ui(new Ui::createdatabase) {
    ui->setupUi(this);
}

createdatabase::~createdatabase() {
    delete ui;
}
