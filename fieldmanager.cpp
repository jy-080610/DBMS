//
// 权限管理，是否允许增插删改字段操作
//

// You may need to build the project (run Qt uic code generator) to get "ui_fieldmanager.h" resolved

#include "fieldmanager.h"
#include "ui_fieldmanager.h"


fieldmanager::fieldmanager(QWidget *parent) :
        QWidget(parent), ui(new Ui::fieldmanager) {
    ui->setupUi(this);
}

fieldmanager::~fieldmanager() {
    delete ui;
}
