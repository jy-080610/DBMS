//
// 数据的增插删改操作
//

// You may need to build the project (run Qt uic code generator) to get "ui_dataoperation.h" resolved

#include "dataoperation.h"
#include "ui_dataoperation.h"


dataoperation::dataoperation(QWidget *parent) :
        QWidget(parent), ui(new Ui::dataoperation) {
    ui->setupUi(this);
}

dataoperation::~dataoperation() {
    delete ui;
}
