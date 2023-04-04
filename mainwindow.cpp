//
// Created by YANG on 2023/4/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_Mainwindow.h"


Mainwindow::Mainwindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::Mainwindow) {
    ui->setupUi(this);
}

Mainwindow::~Mainwindow() {
    delete ui;
}
