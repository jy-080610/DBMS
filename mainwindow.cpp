//
// Created by YANG on 2023/4/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_Mainwindow.h"
#include "landing.h"

Mainwindow::Mainwindow(QWidget *parent) :
        QWidget(parent), ui(new Ui::Mainwindow) {
    ui->setupUi(this);

    landing *l = new landing();
    l->setVisible(true);
    connect(l, SIGNAL(setVisibleSignal()), this, SLOT(setVisibleSlot()));
    this->hide();
}

Mainwindow::~Mainwindow() {
    delete ui;
}

void Mainwindow::setVisibleSlot()
{
    this->setVisible(true);
}