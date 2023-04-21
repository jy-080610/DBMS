//
// Created by YANG on 2023/4/4.
//

// You may need to build the project (run Qt uic code generator) to get "ui_Mainwindow.h" resolved

#include "mainwindow.h"
#include "ui_Mainwindow.h"


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
void Mainwindow::on_run_clicked() {
// 获取关键字列表
    QStringList keywordList = dealwithSql->resolveSql(ui->sqllineEdit->text());

    qDebug() << "list大小为：" + QString::number(keywordList.size());

    // 容错判断
    if (keywordList.size() == 0) {
        QMessageBox::critical(nullptr, "错误", "请检查SQL语句！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }

    // 根据返回的操作类型，进行相关的操作
    switch (keywordList[0].toInt()) {

            // -----数据库管理-----
        case 0:
        {
            auto *userdata = new dbmanager();
            userdata->myCreateDataBase(keywordList[1]);
            break; }

        case 1:
        {
            auto *userdata = new dbmanager();
            userdata->myDeteleDataBase(keywordList[1]);
            break; }

            // -----表管理-----
            // 创建表
        case 2:
        {
            ManageTableBySql mtbs;
            mtbs.createTable(keywordList[1]);
            break;
        }

            // 删除表
        case 3:
        {
            ManageTableBySql mtbs;
            mtbs.deleteTable(keywordList[1]);
            break;
        }

            // -----字段管理-----
            // 增加字段并展示
        case 4: {
            ManageFieldBySql mfbs;
            mfbs.addField2tdf(keywordList);
            displayField(keywordList[1]);
            break;
        }

            // 删除字段并展示
        case 5: {
            ManageFieldBySql mfbs;
            mfbs.deleFileFromtdf(keywordList);
            displayField(keywordList[1]);
            break;
        }

            // 修改字段并展示
        case 6: {
            ManageFieldBySql mfbs;
            mfbs.modifyInfo2tb(keywordList);
            displayField(keywordList[1]);
            break;
        }
        default:
            break;
    }
    displayDir();
}

void Mainwindow::displayField(QString tableName) {
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QFile file(dir->path() + "/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "初始化文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    list = str.split(",");
    QString dbName = list[1];
    QString dirPath = dir->path() + "/data/" + list[1];

    file.close();

    ui->tableWidget->clear();

    QString tablePath = dirPath + "/table/" + tableName + "/" +
                        tableName + ".tdf";

    QFile tempFile(tablePath);
    bool  isTableExist = tempFile.exists();

    if (isTableExist) {
        tablePath = dirPath + "/table/" + tableName + "/" +
                    tableName + ".tdf";
        QFile readFile(tablePath);

        if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream read(&readFile);

        QString str, info;
        QStringList strlist, headlist;
        headlist << "字段名" << "数据类型" << "是否为主键" << "可否为空";
        int rownum = 0, colnum = 4;
        ui->tableWidget->setColumnCount(colnum);

        while (!read.atEnd()) {
            str = read.readLine();

            if (str != "") {
                ui->tableWidget->setRowCount(rownum + 1);
                strlist = str.split(",");
                for (int i = 0; i < colnum; i++) {
                    ui->tableWidget->setItem(rownum, i,
                                             new QTableWidgetItem(strlist[i]));
                }
                rownum++;
            }
        }
        readFile.close();
        ui->tableWidget->setHorizontalHeaderLabels(headlist);
    }
}


void Mainwindow::displayDir() {
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString dirPath = dir->path() + "/data";

    auto *model = new QDirModel();

    ui->treeView->setModel(model);
    ui->treeView->setRootIndex(model->index(dirPath));

    for (int i = 1; i < model->columnCount(); i++)
    {
        ui->treeView->setColumnHidden(i, true);
    }
}

void Mainwindow::on_fieldmanage_clicked() {
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    QString dirPath = dir->path() + "/data/sys/curuse.txt";
    QFile file(dirPath);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    list = str.split(",");
    file.close();

    if (list.length() == 2) {
        FieldManager *fm = new FieldManager();
        fm->show();
    } else {
        QMessageBox::critical(nullptr, "critical message", "请新建或选择数据库",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void Mainwindow::on_datamanage_clicked() {
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    QString dirPath = dir->path() + "/data/sys/curuse.txt";
    QFile file(dirPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    list = str.split(",");
    file.close();

    if (list.length() == 2) {
        auto *dp = new dataoperation();
        dp->show();
    } else {
        QMessageBox::critical(nullptr, "critical message", "请新建或选择数据库",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void Mainwindow::on_tablemanage_clicked() {
    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    QString dirPath = dir->path() + "/data/sys/curuse.txt";

    QFile file(dirPath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();
    list = str.split(",");
    file.close();

    if (list.length() == 2) {
        auto *tml = new tablemanageload();
        tml->show();
    } else {
        QMessageBox::critical(nullptr, "critical message", "请新建或选择数据库",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void Mainwindow::on_create_clicked() {
    auto *cdb = new createdatabase();
    cdb->show();
}

void Mainwindow::on_del_clicked() {
    auto *ddb = new deletedatabase();
    ddb->show();
}







