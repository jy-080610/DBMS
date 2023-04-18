//
//建表操作
//

// You may need to build the project (run Qt uic code generator) to get "ui_creattable.h" resolved

#include "creattable.h"
#include "ui_creattable.h"


creattable::creattable(QWidget *parent) :
        QWidget(parent), ui(new Ui::creattable) {
    ui->setupUi(this);
}

creattable::~creattable() {
    delete ui;
}
