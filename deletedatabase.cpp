//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_deletedatabase.h" resolved

#include "deletedatabase.h"
#include "ui_deletedatabase.h"


deletedatabase::deletedatabase(QWidget *parent) :
        QWidget(parent), ui(new Ui::deletedatabase) {
    ui->setupUi(this);
}

deletedatabase::~deletedatabase() {
    delete ui;
}
