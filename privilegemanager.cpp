#include "privilegemanager.h"
#include "ui_privilegemanager.h"
#include "QFileDialog"
#include "qdebug.h"
#include "qmessagebox.h"

privilegemanager::privilegemanager(QWidget *parent) :
        QWidget(parent),
        ui(new Ui::privilegemanager)
{
    ui->setupUi(this);
    initDir();
}

privilegemanager::~privilegemanager()
{
    delete ui;
}

void privilegemanager::initDir()
{
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QFile file(dir->path() + "/DBMS/data/sys/curuse.txt");

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "initDir文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString     str = read.readLine();

    qDebug() << "用户信息" + str;

    list = str.split(",");
    qDebug() << "list=" << list;

    userName = list[0];
    dbName = list[1];
    dirPath = dir->path() + "/DBMS/data/" + list[1];
    qDebug() << "dirpath=" << dirPath;
    file.close();
}

void privilegemanager::on_querry_clicked() {
    if (this->ui->user->text().isEmpty() ||
        (this->ui->user->text() == "")) {
        QMessageBox::critical(0, "错误", "请输入用户名",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    display();
}

void privilegemanager::on_finish_clicked() {
    privilegePath = dirPath + "/userprivilege.txt";
    qDebug() << "privilegepath=" << privilegePath;

    QFile privilege(privilegePath);

    if (!privilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream read(&privilege);

    QString afterDelPath = dirPath + "/modify.txt";
    QFile   writeFile(afterDelPath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }

    QTextStream write(&writeFile);
    QStringList list;
    QString     str, modUser, isCTB, isDTB, isADT, isDDT, isMDT;

    if (this->ui->createtb->isChecked()) {
        isCTB = "1";
    } else {
        isCTB = "0";
    }

    if (this->ui->deltb->isChecked()) {
        isDTB = "1";
    } else {
        isDTB = "0";
    }

    if (this->ui->adddata->isChecked()) {
        isADT = "1";
    } else {
        isADT = "0";
    }
    if (this->ui->deldata->isChecked()) {
        isDDT = "1";
    } else {
        isDDT = "0";
    }
    if (this->ui->modifydata->isChecked()) {
        isMDT = "1";
    } else {
        isMDT = "0";
    }
    modUser = this->ui->user->text();
    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");

        if (list[0] == modUser) {
            modUser += "," + isCTB + "," + isDTB + "," + isADT + "," + isDDT +
                       "," + isMDT + "\n";
            write << modUser;
        } else {
            write << str + "\n";
        }
    }
    privilege.close();
    privilege.remove();
    writeFile.close();
    writeFile.rename(privilegePath);
    this->ui->textBrowser->clear();
    display();
}
void privilegemanager::on_exit_clicked() {
    this->close();
}
void privilegemanager::display() {
    QStringList p;

    p << "创建表：" << "删除表：" << "增加数据：" << "删除数据：" << "修改数据：";
    qDebug() << "p=" << p;
    privilegePath = dirPath + "/userprivilege.txt";
    qDebug() << "privilegepath=" << privilegePath;
    QFile privilege(privilegePath);
    if (!privilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&privilege);
    QStringList list;
    QString     str, showstr;
    int flag = 0;
    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");
        qDebug() << "list=" << list;

        if (list[0] == this->ui->user->text()) {
            for (int i = 1; i < list.size(); i++) {
                if (list[i] == "1") {
                    list[i] = "有";
                }
                else if (list[i] == "0") {
                    list[i] = "无";
                }
                qDebug() << "list=" << list;
                showstr = "";

                //                showstr=p[i-1]+plist[i]+"\n";
                showstr = p[i - 1] + list[i] + "\n";
                qDebug() << "showstr=" << showstr;
                this->ui->textBrowser->insertPlainText(showstr);
            }
            flag = 1;
        }
    }

    if (flag == 0) {
        QMessageBox::critical(0, "错误", "无此用户名！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
    privilege.close();
}

bool privilegemanager::ctb(QString tablename,QString user) {
    privilegePath = dirPath + "/userprivilege.txt";
    qDebug() << "privilegepath=" << privilegePath;

    QFile privilege(privilegePath);

    if (!privilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&privilege);
    QStringList list;
    QString     str, p1;

    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");
        qDebug() << "list=" << list;

        if (list[0] == user) {
            p1 = list[1];
        }
    }
    tPath = dirPath + "/table/" + tablename + "/privilege.txt";
    qDebug() << "tpath=" << tPath;
    QFile tprivilege(privilegePath);
    if (!tprivilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream tread(&tprivilege);
    QStringList tlist;
    QString     tstr, p2;

    while (!tread.atEnd()) {
        tstr = tread.readLine();
        tlist = tstr.split(",");
        qDebug() << "tlist=" << tlist;

        if (tlist[0] == user) {
            p2 = tlist[1];
        }
    }

    if ((p1 == "1")&&(p2=="1")) {
        return true;
    }
    else return false;

    tprivilege.close();
    privilege.close();
}

bool privilegemanager::dtb(QString tablename,QString user) {
    privilegePath = dirPath + "/userprivilege.txt";
    qDebug() << "privilegepath=" << privilegePath;

    QFile privilege(privilegePath);

    if (!privilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&privilege);
    QStringList list;
    QString     str, p1;

    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");
        qDebug() << "list=" << list;

        if (list[0] == user) {
            p1 = list[2];
        }
    }

    tPath = dirPath + "/table/" + tablename + "/privilege.txt";
    qDebug() << "tpath=" << tPath;

    QFile tprivilege(privilegePath);

    if (!tprivilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream tread(&tprivilege);
    QStringList tlist;
    QString     tstr, p2;

    while (!tread.atEnd()) {
        tstr = tread.readLine();
        tlist = tstr.split(",");
        qDebug() << "tlist=" << tlist;

        if (tlist[0] == user) {
            p2 = tlist[2];
        }
    }

    if ((p1 == "1")&&(p2=="1")) {
        return true;
    }
    else return false;

    tprivilege.close();

    privilege.close();
}

bool privilegemanager::adt(QString tablename,QString user) {
    privilegePath = dirPath + "/userprivilege.txt";
    qDebug() << "privilegepath=" << privilegePath;

    QFile privilege(privilegePath);

    if (!privilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&privilege);
    QStringList list;
    QString     str, p1;

    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");
        qDebug() << "list=" << list;

        if (list[0] == user) {
            p1 = list[3];
        }
    }
    tPath = dirPath + "/table/" + tablename + "/privilege.txt";
    qDebug() << "tpath=" << tPath;

    QFile tprivilege(privilegePath);

    if (!tprivilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream tread(&tprivilege);
    QStringList tlist;
    QString     tstr, p2;

    while (!tread.atEnd()) {
        tstr = tread.readLine();
        tlist = tstr.split(",");
        qDebug() << "tlist=" << tlist;

        if (tlist[0] == user) {
            p2 = tlist[3];
        }
    }
    qDebug()<<"tlist="<<tlist;
    qDebug()<<"p2="<<p2;
    qDebug()<<"p1="<<p1;

    if ((p1 == "1")&&(p2=="1")) {
        return true;
    }
    else return false;

    tprivilege.close();
    privilege.close();
}

bool privilegemanager::ddt(QString tablename,QString user) {
    privilegePath = dirPath + "/userprivilege.txt";
    qDebug() << "privilegepath=" << privilegePath;

    QFile privilege(privilegePath);

    if (!privilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&privilege);
    QStringList list;
    QString     str, p1;

    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");
        qDebug() << "list=" << list;

        if (list[0] == user) {
            p1 = list[4];
        }
    }
    tPath = dirPath + "/table/" + tablename + "/privilege.txt";
    qDebug() << "tpath=" << tPath;

    QFile tprivilege(privilegePath);

    if (!tprivilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream tread(&tprivilege);
    QStringList tlist;
    QString     tstr, p2;

    while (!tread.atEnd()) {
        tstr = tread.readLine();
        tlist = tstr.split(",");
        qDebug() << "tlist=" << tlist;

        if (tlist[0] == user) {
            p2 = tlist[4];
        }
    }

    if ((p1 == "1")&&(p2=="1")) {
        return true;
    }
    else return false;

    tprivilege.close();
    privilege.close();
}

bool privilegemanager::mdt(QString tablename,QString user) {
    privilegePath = dirPath + "/userprivilege.txt";
    qDebug() << "privilegepath=" << privilegePath;

    QFile privilege(privilegePath);

    if (!privilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream read(&privilege);
    QStringList list;
    QString     str, p1;

    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");
        qDebug() << "list=" << list;

        if (list[0] == user) {
            p1 = list[5];
        }
    }
    tPath = dirPath + "/table/" + tablename + "/privilege.txt";
    qDebug() << "tpath=" << tPath;

    QFile tprivilege(privilegePath);

    if (!tprivilege.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QTextStream tread(&tprivilege);
    QStringList tlist;
    QString     tstr, p2;

    while (!tread.atEnd()) {
        tstr = tread.readLine();
        tlist = tstr.split(",");
        qDebug() << "tlist=" << tlist;

        if (tlist[0] == user) {
            p2 = tlist[5];
        }
    }

    if ((p1 == "1")&&(p2=="1")) {
        return true;
    }
    else return false;

    tprivilege.close();
    privilege.close();
}

bool privilegemanager::isfuserexist(QString tablename, QString user){
    tPath = dirPath + "/table/" + tablename + "/privilege.txt";

    qDebug() << "isfuserexist当前表权限文件的路径为：" + tPath;
    QFile readFile(tPath);


    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QString str;
    QStringList list,list1;
    int flag=0;

    QTextStream read(&readFile);
    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");
        list1.append(list[0]);
    }
    for(int i=0;i<list1.size();i++){
        if(list1[i]==user){
            flag=1;
        }
    }
    qDebug()<<"isfuserexist flag="<<flag;
    if(flag==1){
        return true;
    }
    else return false;
    readFile.close();
}

bool privilegemanager::isuserexist(QString user){
    QString Path = dirPath + "/userprivilege.txt";

    qDebug() << "isuserexist权限文件的路径为：" + Path;
    QFile readFile(Path);


    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
    }
    QString str;
    QStringList list,list1;
    int flag=0;

    QTextStream read(&readFile);
    while (!read.atEnd()) {
        str = read.readLine();
        list = str.split(",");
        list1.append(list[0]);
    }
    for(int i=0;i<list1.size();i++){
        if(list1[i]==user){
            flag=1;
        }
    }
    qDebug()<<"isuserexist flag="<<flag;
    if(flag==1){
        return true;
    }
    else return false;
    readFile.close();
}

void privilegemanager::initPrivilege(QString tablename,QString user){
    if(isuserexist(user)&&(!isfuserexist(tablename,user))){
        tPath = dirPath + "/table/" + tablename + "/privilege.txt";
        qDebug() << "init当前表权限文件的路径为：" + tPath;
        QFile writeFile(tPath);


        if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Append)) {
            qDebug() << "文件打开失败";
        }

        QTextStream outp(&writeFile);

        outp << user + ",0,0,0,0,0\n";
        writeFile.close();
    }
}

void privilegemanager::grant(QStringList keywordList){
    if ((keywordList[1] == "") ||
        (keywordList[2] == "")) {
        QMessageBox::critical(0, "错误", "请检查基本信息是否正确",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    //初始化表权限
    QStringList userlist;
    QString user;
    user=keywordList[3];
    userlist=user.split(",");
    qDebug()<<"grant:userlist="<<userlist;
    for(int i=0;i<userlist.size();i++){
        qDebug()<<"grant init user:"<<userlist[i];
        initPrivilege(keywordList[2],userlist[i]);
    }

    //
    tPath = dirPath + "/table/" + keywordList[2] + "/privilege.txt";

    qDebug() << "当前表权限文件的路径为：" + tPath;
    QFile readFile(tPath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }

    QTextStream read(&readFile);

    QString afterDelPath = dirPath + "/table/" + keywordList[2]+"/temp.txt";
    QFile writeFile(afterDelPath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream write(&writeFile);
    QStringList privilegelist,list;
    QString privilege,str,str1;

    privilege = keywordList[1];
    privilegelist=privilege.split(",");
    qDebug()<<"privilegelist="<<privilegelist;

    int flag;
    while (!read.atEnd()) {
        flag=0;
        str = read.readLine();
        list = str.split(",");
        qDebug()<<"grant:list="<<list;

        for(int i=0;i<userlist.size();i++){
            for(int i=0;i<privilegelist.size();i++){
                if(privilegelist[i]=="create"){
                    list[1]="1";
                }
                else if(privilegelist[i]=="drop"){
                    list[2]="1";
                }
                else if(privilegelist[i]=="update"){
                    list[3]="1";
                }
                else if(privilegelist[i]=="insert"){
                    list[4]="1";
                }
                else if(privilegelist[i]=="delete"){
                    list[5]="1";
                }
            }
            if(list[0]==userlist[i]){
                str1=list[0]+","+list[1]+","+list[2]+","+list[3]+","+list[4]+","+list[5];
                flag=1;
            }
        }
        qDebug()<<"grant:str="<<str;
        qDebug()<<"grant:str1="<<str1;
        if(flag==1){
            write <<str1+"\n";
        }
        else{
            write <<str+"\n";
        }
    }
    QMessageBox::information(0,
                             "通知",
                             "授权成功",
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::Cancel | QMessageBox::Escape, 0);


    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(tPath);

}

void privilegemanager::revoke(QStringList keywordList){
    if ((keywordList[1] == "") ||
        (keywordList[2] == "")) {
        QMessageBox::critical(0, "错误", "请检查基本信息是否正确",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
        return;
    }
    //初始化表权限
    QStringList userlist;
    QString user;
    user=keywordList[3];
    userlist=user.split(",");
    qDebug()<<"grant:userlist="<<userlist;
    for(int i=0;i<userlist.size();i++){
        qDebug()<<"grant init user:"<<userlist[i];
        initPrivilege(keywordList[2],userlist[i]);
    }
    tPath = dirPath + "/table/" + keywordList[2] + "/privilege.txt";

    qDebug() << "当前表权限文件的路径为：" + tPath;
    QFile readFile(tPath);

    if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }

    QTextStream read(&readFile);

    QString afterDelPath = dirPath + "/table/" + keywordList[2]+"/temp.txt";
    QFile writeFile(afterDelPath);

    if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败";
        return;
    }
    QTextStream write(&writeFile);
    QStringList privilegelist,list;
    QString privilege,str,str1;

    privilege = keywordList[1];
    privilegelist=privilege.split(",");
    qDebug()<<"privilegelist="<<privilegelist;

    int flag;
    while (!read.atEnd()) {
        flag=0;
        str = read.readLine();
        list = str.split(",");
        qDebug()<<"grant:list="<<list;

        for(int i=0;i<userlist.size();i++){
            for(int i=0;i<privilegelist.size();i++){
                if(privilegelist[i]=="create"){
                    list[1]="0";
                }
                else if(privilegelist[i]=="drop"){
                    list[2]="0";
                }
                else if(privilegelist[i]=="update"){
                    list[3]="0";
                }
                else if(privilegelist[i]=="insert"){
                    list[4]="0";
                }
                else if(privilegelist[i]=="delete"){
                    list[5]="0";
                }
            }
            qDebug()<<"grant:list="<<list;
            if(list[0]==userlist[i]){
                str1=list[0]+","+list[1]+","+list[2]+","+list[3]+","+list[4]+","+list[5];
                flag=1;
            }
        }
        qDebug()<<"grant:str="<<str;
        qDebug()<<"grant:str1="<<str1;
        if(flag==1){
            write <<str1+"\n";
        }
        else{
            write <<str+"\n";
        }
    }
    QMessageBox::information(0,
                             "通知",
                             "权限收回成功",
                             QMessageBox::Ok | QMessageBox::Default,
                             QMessageBox::Cancel | QMessageBox::Escape, 0);


    readFile.close();
    readFile.remove();
    writeFile.close();
    writeFile.rename(tPath);

}
