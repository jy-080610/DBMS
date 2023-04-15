//
// Created by 52750 on 2023/4/15.
//

// You may need to build the project (run Qt uic code generator) to get "ui_table.h" resolved

#include "table.h"
#include "ui_table.h"


table::table(QWidget *parent) :
        QWidget(parent), ui(new Ui::table) {
    ui->setupUi(this);
}

table::~table() {
    delete ui;
}
