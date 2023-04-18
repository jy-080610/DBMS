//
// Created by Asus on 2023/4/17.
//

// You may need to build the project (run Qt uic code generator) to get "ui_privilegemanager.h" resolved

#include "privilegemanager.h"
#include "ui_privilegemanager.h"


privilegemanager::privilegemanager(QWidget *parent) :
        QWidget(parent), ui(new Ui::privilegemanager) {
    ui->setupUi(this);
}

privilegemanager::~privilegemanager() {
    delete ui;
}
