//
// 字段约束条件管理
//

#include "fieldmanager.h"
#include "ui_fieldmanager.h"
#include "QFileDialog"
#include "qdebug.h"
#include "tablemanager.h"
#include "qmessagebox.h"
#include "dataoperation.h"

FieldManager::FieldManager(QWidget *parent) :
        QWidget(parent), ui(new Ui::FieldManager) {
    ui->setupUi(this);
    initDir();
}

FieldManager::~FieldManager() {
    delete ui;
}
void FieldManager::initDir() {
    QDir *dir=new QDir(QDir::currentPath());
    dir->cdUp();//返回上一层目录
    QFile file(dir->path() + "/data/sys/curuse.txt");
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString str =read.readLine();
    list=str.split(",");
    userName = list[0];
    dbName = list[1];
    dirPath = dir->path() + "/data/" + list[1];
    file.close();

}
//增加字段
void FieldManager::on_add_clicked() {
    if ((this->ui->path->text() == "") || this->ui->fieldNameEdit->text().isEmpty() ||
        (this->ui->fieldNameEdit->text() == "")) {
        QMessageBox::critical(0, "错误", "字段名不能为空", QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    //判断字段名是否重复
    if (isDuplicate(this->ui->fieldNameEdit->text())) {
        QMessageBox::critical(0, "错误", "字段名重复", QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +this->ui->path->text() + ".tdf";
    QFile checkFile(tablePath);
    if (!checkFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&checkFile);//读取文件内容
    QString isPK;
    QString isNull;
    //判断是否是主键且是否有主键存在
    if (this->ui->isPK->isChecked()) {
        QString textInfo = read.readAll();//读取文件内容，判断是否有主键存在
        if (textInfo.contains("主键")) {
            QMessageBox::critical(0, "错误", "主键已存在", QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }
        isPK = "主键";
    } else {
        isPK = "非主键";
    }
    if (this->ui->isNull->isChecked()) {
        isNull = "可为空";
    }else{
        isNull = "非空";
    }
    QFile file(tablePath);
    if (!file.open(QIODevice::WriteOnly|QIODevice::Append | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }

    QTextStream write(&file);
    QString insertInfo="";
    //写入字段约束条件
    insertInfo += this->ui->fieldNameEdit->text() + "," +
                  this->ui->dataType->currentText() + "," +
                  isPK + "," +
                  isNull + "\n";
    write << insertInfo;
    file.close();
    QMessageBox::information(0, "提示", "添加成功", QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::Cancel | QMessageBox::Escape, 0);
    display();
    addComma2trd();//在数据记录中添加一列
    TableManager TM(userName,dbName);
    TM.tableModifier(this->ui->path->text(),1);
}

void FieldManager::on_modify_clicked() {
    if (this->ui->path->text().isEmpty()||
            ( this->ui->fieldNameEdit->text().isEmpty())||
            (this->ui->fieldNameEdit->text()=="")){
        QMessageBox::critical(0, "错误", "字段名不能为空", QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);

    return ;
    }
    tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +this->ui->path->text() + ".tdf";
    QFile checkFile(tablePath);
    if (!checkFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return;
    }
    QTextStream checkText(&checkFile);
    //主键检查，若将该段改为主键，检查是否有主键存在
    if (this->ui->isPK->isChecked()){
        QString textInfo=checkText.readAll();//读取文件内容，判断是否有主键存在
        if (textInfo.contains("主键")){
            QMessageBox::critical(0, "错误", "主键已存在", QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }
    }
    checkFile.close();
    QString afterDelPath = dirPath + "/table/" + this->ui->path->text() +"/modify.tdf";
    QFile writeFile(afterDelPath);
    if (!writeFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return;
    }
    QTextStream write(&writeFile);
    QStringList list;
    QString str;
    QString modInfo;
    QString isPK;
    QString isNull;

    if(this->ui->isPK->isChecked()){
        isPK="主键";
    } else{
        isPK="非主键";
    }
    if(this->ui->isNull->isChecked()){
        isNull="可为空";
    } else{
        isNull="非空";
    }
    modInfo= this->ui->fieldNameEdit->text();
    QFile readFile(tablePath);
    if (!readFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return;
    }
    QTextStream read(&readFile);
    while(!read.atEnd()){
        str=read.readLine();
        list=str.split(",");
        if(list[0]==modInfo){
            modInfo=","+this->ui->dataType->currentText()+","+isPK+","+isNull+"\n";
            qDebug()<<"modInfo:"<<modInfo;
            write<<modInfo;
        }else{
            write<<str+"\n";
        }
    }

    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(tablePath);
    display();
    //更新定义表
    TableManager TM(userName,dbName);
    TM.tableModifier(this->ui->path->text(),3);
}

void FieldManager::on_dele_clicked() {
    if(this->ui->path->text().isEmpty()||
            ( this->ui->fieldNameEdit->text().isEmpty())||
            (this->ui->fieldNameEdit->text()=="")){
        QMessageBox::critical(0, "错误", "字段名不能为空", QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +this->ui->path->text() + ".tdf";
    QFile readFile(tablePath);
    if (!readFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return;
    }
    QTextStream read(&readFile);
    QString afterDelPath = dirPath + "/table/" + this->ui->path->text() +"/del.tdf";
    QFile writeFile(afterDelPath);
    if (!writeFile.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return;
    }
    QTextStream write(&writeFile);
    QStringList list;
    QString str;
    QString delInfo;
    delInfo=this->ui->fieldNameEdit->text();
    int deleColId=1;
    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");
        if (list[0] == delInfo) {
            qDebug() << "delecolid=" << deleColId;
            // 删除相应的数据
            removedata(deleColId - 1);
        }
        else {
            write << str + "\n";
            deleColId++;
        }
    }
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(tablePath);
    display();
    //更新定义表
    TableManager TM(userName,dbName);
    TM.tableModifier(this->ui->path->text(),4);

}

void FieldManager::on_display_clicked() {
    if (this->ui->path->text().isEmpty() ||
        (this->ui->path->text() == "")) {
        QMessageBox::critical(0, "错误", "表名不能为空",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    display();
}

void FieldManager::on_isPK_clicked() {
    if (ui->isPK->isChecked()) {
        ui->isNull->setChecked(false);
    }
}

void FieldManager::on_isNull_clicked() {
    if (ui->isPK->isChecked()) {
        ui->isNull->setChecked(false);
    } else if (ui->isNull->isChecked()) {
        ui->isNull->setChecked(true);
    } else {
        ui->isNull->setChecked(false);
    }
}


//表是否是已经存在
bool FieldManager::isTableExist() {
    tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +this->ui->path->text() + ".tdf";
    QFile tempFile(tablePath);
    return tempFile.exists();
}

void FieldManager::display() {
    ui->tableWidget->clear();
    // 当指定的表存在时，进行展示操作
    if (isTableExist()) {
        // 以只读方式打开对应文件
        tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +
                    this->ui->path->text() + ".tdf";
        QFile readFile(tablePath);
        if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream read(&readFile);
        QString     str, info;
        QStringList strlist, headlist;

        // 表头赋值
        headlist << "字段名" << "数据类型" << "是否为主键" << "可否为空";

        // 定义行号和列号
        int rownum = 0, colnum = 4;
        ui->tableWidget->setColumnCount(colnum);
        // 逐行读取文件信息并给UI赋值
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
        // 添加表头
        ui->tableWidget->setHorizontalHeaderLabels(headlist);
    }

}
//判断字段是否重复
bool FieldManager::isDuplicate(QString fieldName) {

    tablePath = dirPath + "/table/" + this->ui->path->text() + "/" +this->ui->path->text() + ".tdf";
    qDebug()<<"tablePath:"<<tablePath;
    QFile file(tablePath);
    if (!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return false;
    }
    QTextStream read(&file);
    QStringList list;
    QString readinfo;
    while(!read.atEnd()){
        readinfo=read.readLine();
        list=readinfo.split(",");
        if(list[0]==fieldName){
            return true;
        }
    }
      return false;
}
//添加字段后保证字段数据的一致性
void FieldManager::addComma2trd() {
    QString trdPath=dirPath+"/table/"+this->ui->path->text()+"/"+this->ui->path->text()+".trd";
    QFile readFile(trdPath);
    if (!readFile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
        return;
    }
    QTextStream read(&readFile);
    QString afterAddPath = dirPath + "/table/" + this->ui->path->text() +"/modify.trd";
    QFile writeFile(afterAddPath);
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QString     str;

    // 将修改后的内容写入新文件
    while (!read.atEnd()) {
        str = read.readLine();
        write << str + ",\n";
    }
    // 用新文件替换掉旧文件
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(trdPath);
}
//根据删除的字段列号来删除对应的数据列
void FieldManager::removedata(int datacol) {
    QString trdPath = dirPath + "/table/" + this->ui->path->text() + "/" +
                      this->ui->path->text() + ".trd";
    QFile readFile(trdPath);
    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&readFile);
    QString     afterDeletePath = dirPath + "/table/" + this->ui->path->text() +
                                  "/modify.trd";
    QFile writeFile(afterDeletePath);
    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream write(&writeFile);
    QString     str1,str2;
    QStringList list;
    int col=datacol;
    // 从旧文件逐行读取信息,将每一行信息依次进行修改，删除对应的那一列后写入到新文件中
    while (!read.atEnd()) {//读取每一行
        str2 = "";//每一行的数据
        str1 = read.readLine();//读取每一行的数据
        list = str1.split(",");//将每一行的数据以逗号分隔
        qDebug() << "col=" << col;//删除的列号
        list.removeAt(col);//删除对应的列
        qDebug() << "after remove list=" << list;
        int j;

        for (j = 0; j < list.size(); j++) {//将删除后的数据重新写入到新文件中
            if (j < list.size() - 1) {//如果不是最后一列
                str2 = str2 + list[j] + ",";//将数据以逗号分隔
            }
            else if (j == list.size() - 1) {//如果是最后一列
                str2 = str2 + list[j];
            }
            qDebug() << "str2=" << str2;
        }
        write << str2 + "\n";//将修改后的数据写入到新文件中
    }

    // 新文件替换旧文件
    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(trdPath);


}

void FieldManager::on_exit_clicked() {
   this->close();
}
