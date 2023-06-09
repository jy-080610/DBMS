//
// 数据的增插删改保存操作
//

// You may need to build the project (run Qt uic code generator) to get "ui_dataoperation.h" resolved

#include "dataoperation.h"
#include "ui_dataoperation.h"
#include "privilegemanager.h"
#include "QFileDialog"
#include "qdebug.h"
#include "qmessagebox.h"
#include "iostream"
#include "fstream"
#include "sstream"
#include <QTimer>
#include <QDateTime>
using namespace std;

dataoperation::dataoperation(QWidget *parent) :
        QWidget(parent), ui(new Ui::dataoperation) {
    ui->setupUi(this);
    initDir();//初始化文件夹
}

dataoperation::~dataoperation() {
    delete ui;
}
//初始化文件夹
void dataoperation::initDir() {
        QDir *dir = new QDir(QDir::currentPath());
        dir->cdUp();
        QFile file(dir->path() + "/data/sys/curuse.txt");
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
        }
        QTextStream read(&file);
        QStringList list;
        QString str = read.readLine();
        list = str.split(",");
        user=list[0];
        dirPath= dir->path() + "/data/" + list[1];
        qDebug() << dirPath;
        file.close();
}
bool dataoperation::isDigitString(const QString& src) {
    const char *s=src.toUtf8().data();//将QString转char*
    while (*s && *s >= '0' && *s <= '9') s++;
    return !bool (*s);//如果是数字返回true
}
//判断是否为日期
bool dataoperation::isDateString(QString str) {
    QDateTime date = QDateTime::fromString(str, "yyyyMMdd");//设置时间格式
    bool res;
    if(str==""){
        return true;
    }
    else res=date.isValid();//判断是否为日期,isvalid()函数用于判断是否为有效的日期,返回值为bool类型
    if(res){//如果是日期
       qDebug()<<"是日期"<<res;
    }
    else{
        qDebug()<<"不是日期"<<res;

    }
    return res;
}

void dataoperation::on_pushButton_clicked() {
    //表文件
    QString fileName=dirPath+"/table/"+
            this->ui->path->text()+"/"+
            this->ui->path->text()+".trd";
    qDebug()<<"fileName:"<<fileName;
    filename =fileName;
    //字段文件
    QString tablePath=dirPath+"/table/"+
            this->ui->path->text()+"/"+
            this->ui->path->text()+".tdf";
    qDebug()<<"tablePath:"<<tablePath;
    QFile tablefile(tablePath);
    if (!tablefile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream readtable(&tablefile);
    QStringList tablelist;
    QStringList headlist;
    QString readinfo;
    //表头
    while(!readtable.atEnd()) {
        readinfo = readtable.readLine();//读取一行
        tablelist = readinfo.split(",");//分割
        headlist.append(tablelist[0]);//表头
    }

    //列数，属性数目
    QString tableP=dirPath+"/table/"+
            this->ui->path->text()+"/"+
            this->ui->path->text()+".tdf";
    qDebug()<<"tableP:"<<tableP;
    QFile tablef(tableP);
    if (!tablef.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream readt(&tablef);
    QString readi;
    int n=0;
    while(!readt.atEnd()) {
        readi = readt.readLine();//读取一行
        n++;
    }
    col=n;//列数
    if(!fileName.isEmpty()){//如若文件不为空
        x.clear();
        qv2.clear();//清空

        QFile readfile(fileName);//读取文件
        if(!readfile.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"文件打开失败";
            QMessageBox::warning(this,"警告","文件打开失败,此表不存在");
            return ;
        }
        QTextStream read(&readfile);//读取文件
        QStringList list;
        QString fileLine;
        qDebug()<<"list1="<<list1;
        //读取数据存入QVector
        while(!read.atEnd()){
            fileLine=read.readLine();//读取一行
            list=fileLine.split(",");//分割
          qDebug()<<"list.count="<<list.count();
          x.clear();
          for(int i=0;i<col;i++){
              QString A=list.at(i);//at()函数返回索引为i的元素
              qDebug()<<"A="<<A;
                x.append(A);
              qDebug()<<"x="<<x;
          }
          qv2.append(x);
          qDebug()<<"qv2="<<qv2;
        }
        tablefile.close();
        tablef.close();
        readfile.close();
    }
    int row=qv2.size();//行数
    qDebug()<<"row="<<row;
    qDebug()<<"col="<<col;
    this->ui->tableWidget->setRowCount(row);//设置行数
    this->ui->tableWidget->setColumnCount(col);//设置列数
    this->ui->tableWidget->setHorizontalHeaderLabels(headlist);//设置表头
    this->ui->tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);//设置表头自适应
    this->ui->tableWidget->setItem(0,0,new QTableWidgetItem("1"));
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            this->ui->tableWidget->setItem(i, j, new QTableWidgetItem(qv2[i][j]));
        }
    }

    }


//插入
void dataoperation::on_pushButton_insert_clicked() {
    privilegemanager ifmdt;
    if(ifmdt.adt(this->ui->path->text(),user)){
        int row=ui->tableWidget->rowCount();//获取行数
        ui->tableWidget->insertRow(row);//插入一行
        for(int j=0;j<col;j++){
            this->ui->tableWidget->setItem(row,j,new QTableWidgetItem(""));
        }
    } else{
        QMessageBox::critical(nullptr,"警告","您没有权限向此表插入数据",QMessageBox::Ok|QMessageBox::Default,
                              QMessageBox::Cancel|QMessageBox::Escape,0);
    }

}
//删除一行
void dataoperation::on_pushButton_delete_clicked() {
    privilegemanager ifmdt;
    if(ifmdt.ddt(this->ui->path->text(),user)){
        int i = ui->tableWidget->currentRow();//获取当前行

        ui->tableWidget->removeRow(i);//删除一行
        ui->tableWidget->setFocusPolicy(Qt::NoFocus);//设置焦点
    }
    else{
        QMessageBox::critical(nullptr, "错误", "您没有权限向此表删除数据！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void dataoperation::on_pushButton_save_clicked() {
    privilegemanager ifmdt;
    if(ifmdt.mdt(this->ui->path->text(),user)){
        save();
    }
    else{
        QMessageBox::critical(nullptr, "错误", "您没有权限！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }

}

void dataoperation::on_pushButton_exit_clicked() {
    this->close();//关闭窗口
}


void dataoperation::save() {
    QFile file2(filename);//打开文件
    if(!file2.open(QIODevice::WriteOnly | QIODevice::Text)){
        qDebug()<<"文件保存失败";
        QMessageBox::critical(this,"错误",tr("File saving failed!"),
                              QMessageBox::Yes, QMessageBox::Yes);
    }
    else{
        QTextStream stream(&file2);
        QString conTents;
        QString tablePath=dirPath+"/table/"+
                this->ui->path->text()+"/"+
                this->ui->path->text()+".tdf";
        QFile tablefile(tablePath);
        if(!tablefile.open(QIODevice::ReadOnly | QIODevice::Text)){
            qDebug()<<"文件打开失败";
            QMessageBox::critical(this,"错误",tr("文件打开失败"),
                                  QMessageBox::Yes, QMessageBox::Yes);
        }
        QTextStream readcon(&tablefile);//读取文件
        QStringList collist;
        QStringList conlist;
        QString readinfo;
        int flag=0;

        for(int j=0;j<ui->tableWidget->columnCount();j++){
            readinfo=readcon.readLine();//读取一行
            conlist=readinfo.split(",");//分割
            collist.clear();
            for(int i=0;i<ui->tableWidget->rowCount();i++){
                QTableWidgetItem *item=ui->tableWidget->item(i,j);
                if(conlist[1]=="number" && !isDigitString(item->text()) ){
                    flag=1;
                }

                else if(conlist[1]=="date" && !isDateString(item->text()) ){
                    flag=1;
                }
                else if(conlist[3]=="非空" && item->text()==nullptr ){
                    flag=3;//非空
                }
                collist.append(item->text());//添加到列表
            }
            if (conlist[2]=="主键" && hasSame(collist)){
                flag=2;//主键重复
            }
        }

        qDebug()<<"flag="<<flag;
        for(int i=0;i<ui->tableWidget->rowCount();i++)
        {
            for(int j=0;j<ui->tableWidget->columnCount();j++)
            {
                QTableWidgetItem *item=ui->tableWidget->item(i,j);
                if(!item){//如果为空
                    continue;
                }

                QString str=item->text();
                str.replace(",", " ");
                if(j<ui->tableWidget->columnCount()-1){//如果不是最后一列
                    conTents+=str+",";//添加逗号
                }
                else{
                    conTents+=str;//最后一列不添加逗号
                }


            }
            conTents+="\n";//换行

        }
        if(flag==1){
            QMessageBox::critical(this,"错误",tr("数据类型不匹配"),
                                  QMessageBox::Yes, QMessageBox::Yes);
        }
        else if(flag==2){
            QMessageBox::critical(this,"错误",tr("主键重复"),
                                  QMessageBox::Yes, QMessageBox::Yes);
        }
        else if(flag==3){
            QMessageBox::critical(this,"错误",tr("非空属性不能为空"),
                                  QMessageBox::Yes, QMessageBox::Yes);
        }
        else if(flag==0){
            stream<<conTents;
            QMessageBox::information(this,"提示",tr("保存成功"),
                                     QMessageBox::Yes, QMessageBox::Yes);
            file2.close();//关闭文件
        }
    }

}

bool dataoperation::hasSame(QStringList list) {
    int i=0;
    int j=0;
    int flag =0;
    for (int i = 0; i < list.size(); i++) {
        for (int j = i + 1; j < list.size(); j++) {

                qDebug()<<"list[i]:"<<list[i];
                qDebug()<<"list[j]:"<<list[j];
            if (list[i] == list[j]) {
                flag = 1;
            }
        }
    }
        if (flag==0){
            qDebug()<<"没有重复";
            return false;
        }
        else
            qDebug()<<"有重复";
            return true;




}
