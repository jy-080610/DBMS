//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_deletetable.h" resolved

#include "deletetable.h"
#include "ui_deletetable.h"


deletetable::deletetable(QWidget *parent) :
        QWidget(parent), ui(new Ui::deletetable) {
    ui->setupUi(this);
}

deletetable::~deletetable() {
    delete ui;
}
