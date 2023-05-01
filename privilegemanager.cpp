
//用户权限管理
// You may need to build the project (run Qt uic code generator) to get "ui_privilegemanager.h" resolved

#include "privilegemanager.h"
#include "ui_privilegemanager.h"
#include "QFileDialog"
#include "qdebug.h"
#include "qmessagebox.h"
privilegemanager::privilegemanager(QWidget *parent) :
        QWidget(parent), ui(new Ui::privilegemanager) {
    ui->setupUi(this);
}

privilegemanager::~privilegemanager() {
    delete ui;
}
void privilegemanager::initDir() {
     QDir *dir=new QDir(QDir::currentPath());//获取当前路径
    qDebug()<<"privilegemanager当前目录路径："<<dir->path();
        dir->cdUp();//返回上一级目录
        QFile file(dir->path()+"/DBMS/data/sys/curuse.txt");//打开当前使用的数据库
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            qDebug()<<"文件打开失败";
            QMessageBox::warning(this,"警告","文件打开失败");
            return;
        }
        QTextStream read(&file);//读取文件
        QStringList list;//创建字符串列表
        QString str=read.readLine();//读取一行
        qDebug()<<"用户信息："+str;
        list=str.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"list="<<list;
        userName=list[0];//获取当前用户名
        dbName=list[1];//获取当前数据库名
        dirPath=dir->path()+"/DBMS/data/"+list[1];//当前数据库的路径
        qDebug()<<"dirPath="<<dirPath;//输出当前数据库的路径
        file.close();//关闭文件

}

//创建表
bool privilegemanager::ctb(QString tablename, QString user) {
    privilegePath=dirPath+"/userprivilege.txt";//用户权限文件路径
    qDebug()<<"privilegePath="<<privilegePath;//输出用户权限文件路径
    QFile privilege(privilegePath);//打开用户权限文件
    if(!privilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QTextStream read(&privilege);//读取文件
    QStringList list;//创建字符串列表
    QString str;
    QString  p1;
    while(!read.atEnd()){
        str=read.readLine();//读取一行
        list=str.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"list="<<list;
        if(list[0]==user){
            p1=list[1];
            qDebug()<<"p1="<<p1;
        }
    }
    tPath = dirPath + "/table/" + tablename+"/privilege.txt";//表权限文件路径
    qDebug()<<"tPath="<<tPath;//输出表权限文件路径
    QFile tprivilege(privilegePath);//打开表权限文件
    if(!tprivilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QTextStream tread(&tprivilege);//读取文件
    QStringList tlist;//创建字符串列表
    QString tstr;
    QString  p2;
    while(!tread.atEnd()){
        tstr=tread.readLine();//读取一行
        tlist=tstr.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"tlist="<<tlist;
        if(tlist[0]==user){
            p2=tlist[1];
            qDebug()<<"p2="<<p2;
        }
    }
    if(p1=="1"&&p2=="1"){
        return true;
    }
    else
        return false;

    tprivilege.close();//关闭文件
    privilege.close();//关闭文件
}
//删除表
bool privilegemanager::dtb(QString tablename, QString user) {
    privilegePath=dirPath+"/userprivilege.txt";//用户权限文件路径
    qDebug()<<"privilegePath="<<privilegePath;//输出用户权限文件路径
    QFile privilege(privilegePath);//打开用户权限文件
    if(!privilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QTextStream read(&privilege);//读取文件
    QStringList list;//创建字符串列表
    QString str;
    QString  p1;
    while(!read.atEnd()){
        str=read.readLine();//读取一行
        list=str.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"list="<<list;
        if(list[0]==user){
            p1=list[2];
            qDebug()<<"p1="<<p1;
        }
    }
    tPath = dirPath + "/table/" + tablename+"/privilege.txt";//表权限文件路径
    qDebug()<<"tPath="<<tPath;//输出表权限文件路径
    QFile tprivilege(privilegePath);//打开表权限文件
    if(!tprivilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QTextStream tread(&tprivilege);//读取文件
    QStringList tlist;//创建字符串列表
    QString tstr;
    QString  p2;
    while(!tread.atEnd()){
        tstr=tread.readLine();//读取一行
        tlist=tstr.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"tlist="<<tlist;
        if(tlist[0]==user){
            p2=tlist[2];
            qDebug()<<"p2="<<p2;
        }
    }
    if(p1=="1"&&p2=="1"){
        return true;
    }
    else{
        return false;
    }
    tprivilege.close();//关闭文件
    privilege.close();//关闭文件

}
//修改表
bool privilegemanager::adt(QString tablename, QString user) {
    privilegePath=dirPath+"/userprivilege.txt";//用户权限文件路径
    qDebug()<<"privilegePath="<<privilegePath;//输出用户权限文件路径
    QFile privilege(privilegePath);//打开用户权限文件
    if(!privilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QTextStream read(&privilege);//读取文件
    QStringList list;//创建字符串列表
    QString str;
    QString  p1;
    while(!read.atEnd()){
        str=read.readLine();//读取一行
        list=str.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"list="<<list;
        if(list[0]==user){
            p1=list[3];
            qDebug()<<"p1="<<p1;
        }
    }
    tPath = dirPath + "/table/" + tablename+"/privilege.txt";//表权限文件路径
    qDebug()<<"tPath="<<tPath;//输出表权限文件路径
    QFile tprivilege(privilegePath);//打开表权限文件
    if(!tprivilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QTextStream tread(&tprivilege);//读取文件
    QStringList tlist;//创建字符串列表
    QString tstr;
    QString  p2;
    while(!tread.atEnd()){
        tstr=tread.readLine();//读取一行
        tlist=tstr.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"tlist="<<tlist;
        if(tlist[0]==user){
            p2=tlist[3];
            qDebug()<<"p2="<<p2;
        }
    }
    if(p1=="1"&&p2=="1"){
        return true;
    }
    else
        return false;

    tprivilege.close();//关闭文件
    privilege.close();//关闭文件

}
//删除表
bool privilegemanager::ddt(QString tablename, QString user) {
    privilegePath=dirPath+"/userprivilege.txt";
    qDebug()<<"privilegePath="<<privilegePath;//输出用户权限文件路径
    QFile privilege(privilegePath);//打开用户权限文件
    if(!privilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QTextStream read(&privilege);//读取文件
    QStringList list;//创建字符串列表
    QString str;
    QString  p1;
    while(!read.atEnd()){
        str=read.readLine();//读取一行
        list=str.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"list="<<list;
        if(list[0]==user){
            p1=list[4];
            qDebug()<<"p1="<<p1;
        }
    }
    tPath = dirPath + "/table/" + tablename+"/privilege.txt";//表权限文件路径
    qDebug()<<"tPath="<<tPath;//输出表权限文件路径
    QFile tprivilege(privilegePath);//打开表权限文件
    if(!tprivilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QTextStream tread(&tprivilege);//读取文件
    QStringList tlist;//创建字符串列表
    QString tstr;
    QString  p2;
    while(!tread.atEnd()){
        tstr=tread.readLine();//读取一行
        tlist=tstr.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"tlist="<<tlist;
        if(tlist[0]==user){
            p2=tlist[4];
            qDebug()<<"p2="<<p2;
        }
    }
    if(p1=="1"&&p2=="1"){
        return true;
    }
    else
        return false;

    tprivilege.close();//关闭文件
    privilege.close();//关闭文件

}
//查询表
bool privilegemanager::mdt(QString tablename, QString user) {
   privilegePath=dirPath+"/userprivilege.txt";//用户权限文件路径
    qDebug()<<"privilegePath="<<privilegePath;//输出用户权限文件路径
    QFile privilege(privilegePath);//打开用户权限文件
    if(!privilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QTextStream read(&privilege);//读取文件
    QStringList list;//创建字符串列表
    QString str;
    QString  p1;
    while(!read.atEnd()){
        str=read.readLine();//读取一行
        list=str.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"list="<<list;
        if(list[0]==user){
            p1=list[5];
            qDebug()<<"p1="<<p1;
        }
    }
    tPath = dirPath + "/table/" + tablename+"/privilege.txt";//表权限文件路径
    qDebug()<<"tPath="<<tPath;//输出表权限文件路径
    QFile tprivilege(privilegePath);//打开表权限文件
    if(!tprivilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QTextStream tread(&tprivilege);//读取文件
    QStringList tlist;//创建字符串列表
    QString tstr;
    QString  p2;
    while(!tread.atEnd()){
        tstr=tread.readLine();//读取一行
        tlist=tstr.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"tlist="<<tlist;
        if(tlist[0]==user){
            p2=tlist[5];
            qDebug()<<"p2="<<p2;
        }
    }
    if(p1=="1"&&p2=="1"){
        return true;
    }
    else
        return false;

    tprivilege.close();//关闭文件
    privilege.close();//关闭文件

}


//查询
void privilegemanager::on_querry_clicked() {
        if(this->ui->user->text().isEmpty()||this->ui->user->text()==""){
            QMessageBox::critical(0,"错误","请输入用户名",
                                QMessageBox::Ok|QMessageBox::Default,
                                QMessageBox::Cancel|QMessageBox::Escape,0);
        qDebug()<<"请输入用户名(查询时用户名不能为空)";
        return;
        }
        display();//显示查询结果
}
//完成授权/撤回操作
void privilegemanager::on_finish_clicked() {
    privilegePath=dirPath+"/userprivilege.txt";//用户权限文件路径
    qDebug()<<"privilegePath="<<privilegePath;//输出用户权限文件路径
    QFile privilege(privilegePath);//打开用户权限文件
    if(!privilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return;
    }
    QTextStream read(&privilege);//读取文件
    QString afterDelPath=dirPath+"/modify.txt";//改变后的用户权限文件路径
    qDebug()<<"afterDelPath="<<afterDelPath;//输出改变后的用户权限文件路径
    QFile writeFile(afterDelPath);//打开改变后的用户权限文件
    if(!writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return;
    }
    QTextStream write(&writeFile);//写入文件
    QStringList list;//创建字符串列表
    QString str;
    QString modUser;//要修改的用户
    QString isCTB;//是否有创建表
    QString isDTB;//是否有删除表
    QString isADT;//是否有增加数据
    QString isDDT;//是否有删除数据
    QString isMDT;//是否有修改数据
    if (this->ui->createtb->isChecked()) {//创建表权限
        isCTB="1";
    }
    else{
        isCTB="0";
    }
    if (this->ui->deltb->isChecked()) {//删除表权限
        isDTB="1";
    }
    else{
        isDTB="0";
    }
    if (this->ui->adddata->isChecked()) {//增加数据权限
        isADT="1";
    }
    else{
        isADT="0";
    }
    if (this->ui->deldata->isChecked()) {//删除数据权限
        isDDT="1";
    }
    else{
        isDDT="0";
    }
    if (this->ui->modifydata->isChecked()) {//修改数据权限
        isMDT="1";
    }
    else{
        isMDT="0";
    }
    modUser=this->ui->user->text();//要修改的用户
    while(!read.atEnd()){
        str=read.readLine();//读取一行
        list=str.split(",");//list中依次存储着当前使用的数据库的用户名，数据库名
        qDebug()<<"list="<<list;
        if(list[0]==modUser){
            modUser=","+isCTB+","+isDTB+","+isADT+","+isDDT+","+isMDT+"\n";
            write<<modUser;
        }else{
            write<<str<<"\n";
        }//写入文件
    }
    privilege.close();//关闭文件
    privilege.remove();//删除文件,remove()函数只能删除文件，不能删除目录
    writeFile.close();//关闭文件
    writeFile.rename(privilegePath);//重命名文件
    this->ui->textBrowser->clear();//清空文本框
    display();//显示查询结果


}

void privilegemanager::on_exit_clicked() {
    this->close();//关闭当前窗口
}


//展示用户权限
void privilegemanager::display() {
    QStringList p;//创建字符串列表
    p << "创建表：" << "删除表：" << "增加数据：" << "删除数据：" << "修改数据：";
    qDebug()<<"p="<<p;//输出p
    privilegePath=dirPath+"/userprivilege.txt";//用户权限文件路径
    qDebug()<<"privilegePath="<<privilegePath;//输出用户权限文件路径
    QFile privilege(privilegePath);//打开用户权限文件
    if(!privilege.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return;
    }
    QTextStream read(&privilege);//读取文件
    QStringList list;
    QString str;
    QString showstr;
    int flag=0;
    while(!read.atEnd()){
        str =read.readLine();//读取一行
        list=str.split(",");//list中依次存储着用户名，数据库名，权限
        qDebug()<<"list="<<list;
        if(list[0]==this->ui->user->text()){
            for (int i = 1; i < list.size(); i++) {
                if(list[i]=="1"){
                    list[i]="有";//有权限
                }
                else if(list[i]=="0"){
                    list[i]="无";//无权限
                }
                qDebug()<<"list="<<list;
                showstr="";
                showstr+=p[i-1]+list[i]+"\n";//拼接字符串
                this->ui->textBrowser->insertPlainText(showstr);//显示权限
            }
            flag=1;
        }
    }

    if(flag==0){
        QMessageBox::critical(0,"错误","用户不存在",
                            QMessageBox::Ok|QMessageBox::Default,
                            QMessageBox::Cancel|QMessageBox::Escape,0);
        qDebug()<<"用户不存在";
    }
    privilege.close();//关闭文件
}
//用户对表的操作权限否存在
bool privilegemanager::isfuserexist(QString tablename, QString user) {
    tPath=dirPath+"/table/"+tablename+"/privilege.txt";//表权限文件路径
    qDebug()<<"存储用户权限的文件路径为tPath："<<tPath;//输出表权限文件路径
    QFile readFile(tPath);//打开表权限文件
    if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QString str;
    QStringList list;
    QStringList list1;
    int flag=0;
    QTextStream read(&readFile);//读取文件
    while(!read.atEnd()){
        str=read.readLine();//读取一行
        list=str.split(",");
        list1.append(list[0]);//将用户名存储到list1中

    }
    //list1用来存储表中的用户名
    for (int i = 0; i < list1.size(); i++) {
        if (list1[i]==user) {
            flag=1;
        }

    }
    qDebug()<<"用户对表的权限操作flag:"<<flag;
    if(flag==1){
        return true;
    }
    else
        return false;

    readFile.close();//关闭文件
}
//用户是否存在
bool privilegemanager::isuserexist(QString user) {
    QString Path=dirPath+"/userprivilege.txt";//用户权限文件路径
    qDebug()<<"存储用户的文件路径为Path："<<Path;//输出用户权限文件路径
    QFile readFile(Path);//打开用户权限文件
    if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return false;
    }
    QString str;
    QStringList list;
    QStringList list1;
    int flag=0;
    QTextStream read(&readFile);//读取文件
    while(!read.atEnd()){
        str=read.readLine();//读取一行
        list=str.split(",");
        list1.append(list[0]);//将用户名存储到list1中

    }
    //list1用来存储表中的用户名
    for (int i = 0; i < list1.size(); i++) {
        if (list1[i]==user) {
            flag=1;
        }

    }
    qDebug()<<"用户是否存在的flag:"<<flag;
    if(flag==1){
        return true;
    }
    else
        return false;

    readFile.close();//关闭文件
}
//初始化用户权限
void privilegemanager::initPrivilege(QString tablename, QString user) {
    if(isuserexist(user)&&(!isfuserexist(tablename,user))){//用户存在且用户对表的操作权限不存在

        tPath=dirPath+"/table/"+tablename+"/privilege.txt";//表权限文件路径
        qDebug()<<"初始化用户权限的文件路径为tPath："<<tPath;//输出表权限文件路径
        QFile writeFile(tPath);//打开表权限文件
        if(!writeFile.open(QIODevice::WriteOnly|QIODevice::Append|QIODevice::Text))
        {
            qDebug()<<"文件打开失败";
            QMessageBox::warning(this,"警告","文件打开失败");
            return;
        }
        QTextStream outp(&writeFile);//写入文件
        outp<<user+",0,0,0,0,0\n";//写入用户权限,0表示无权限，1表示有权限
        writeFile.close();//关闭文件
    }

}
//授权
void privilegemanager::grant(QStringList keywordList) {
    if((keywordList[1]=="")||(keywordList[2]=="")){
        QMessageBox::critical(0,"错误","用户名或表名不能为空,请检查信息是否正确",
                            QMessageBox::Ok|QMessageBox::Default,
                            QMessageBox::Cancel|QMessageBox::Escape,0);
    }
    QStringList userlist;
    QString user;
    user=keywordList[3];
    userlist=user.split(",");//将用户以逗号分隔
    qDebug()<<"userlist="<<userlist;
    for (int i = 0; i < userlist.size(); i++) {
        initPrivilege(keywordList[2],userlist[i]);//初始化用户权限
    }
    tPath=dirPath+"/table/"+keywordList[2]+"/privilege.txt";//表权限文件路径
    qDebug()<<"存储用户权限的文件路径为tPath："<<tPath;//输出表权限文件路径
    QFile readFile(tPath);//打开表权限文件
    if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return;
    }
    QTextStream read(&readFile);//读取文件
    QString afterDelPath=dirPath+"/table/"+keywordList[2]+"/temp.txt";//存储删除后的权限文件路径
    QFile writeFile(afterDelPath);//打开存储删除后的权限文件
    if(!writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return;
    }
    QTextStream write(&writeFile);//写入文件
    QStringList privilegelist;
    QStringList list;
    QString privilege;
    QString str;
    QString str1;
    privilege=keywordList[1];
    privilegelist=privilege.split(",");//将权限以逗号分隔
    qDebug()<<"privilegelist="<<privilegelist;
    int flag;
    while(!read.atEnd()){
        flag=0;
        str=read.readLine();//读取一行
        list=str.split(",");//将一行以逗号分隔
        qDebug()<<"list="<<list;
        for(int i=0;i<userlist.size();i++){
            for(int i=0;i<privilegelist.size();i++){
                if(privilegelist[i]=="create"){//创建
                    list[1]="1";
                }
                else if(privilegelist[i]=="drop"){//删除
                    list[2]="1";
                }
                else if(privilegelist[i]=="update"){//更新
                    list[3]="1";
                }
                else if(privilegelist[i]=="insert"){//插入
                    list[4]="1";
                }
                else if(privilegelist[i]=="delete"){//删除
                    list[5]="1";
                }
            }
            if(list[0]==userlist[i]){//如果用户名相同
                //将权限写入文件
                str1=list[0]+","+list[1]+","+list[2]+","+list[3]+","+list[4]+","+list[5];
                flag=1;
            }

        }
        qDebug()<<"grant:str="<<str;
        qDebug()<<"grant:str1="<<str1;
        if(flag==1){
            write<<str1<<"\n";
        }
        else{
            write<<str<<"\n";
        }
    }
    QMessageBox::information(0,"提示","授权成功",
                        QMessageBox::Ok|QMessageBox::Default,
                        QMessageBox::Cancel|QMessageBox::Escape,0);
    readFile.close();//关闭文件
    readFile.remove();//删除文件
    writeFile.close();//关闭文件
    writeFile.rename(tPath);//重命名文件

}
//回收权限
void privilegemanager::revoke(QStringList keywordList) {
    if((keywordList[1]=="")||(keywordList[2]=="")){
        QMessageBox::critical(0,"错误","用户名或表名不能为空,请检查信息是否正确",
                            QMessageBox::Ok|QMessageBox::Default,
                            QMessageBox::Cancel|QMessageBox::Escape,0);
    }
    QStringList userlist;
    QString user;
    user=keywordList[3];
    userlist=user.split(",");//将用户以逗号分隔
    qDebug()<<"userlist="<<userlist;
    for (int i = 0; i < userlist.size(); i++) {
        initPrivilege(keywordList[2],userlist[i]);//初始化用户权限
    }
    tPath=dirPath+"/table/"+keywordList[2]+"/privilege.txt";//表权限文件路径
    qDebug()<<"存储用户权限的文件路径为tPath："<<tPath;//输出表权限文件路径
    QFile readFile(tPath);//打开表权限文件
    if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return;
    }
    QTextStream read(&readFile);//读取文件
    QString afterDelPath=dirPath+"/table/"+keywordList[2]+"/temp.txt";//存储删除后的权限文件路径
    QFile writeFile(afterDelPath);//打开存储删除后的权限文件
    if(!writeFile.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        qDebug()<<"文件打开失败";
        QMessageBox::warning(this,"警告","文件打开失败");
        return;
    }
    QTextStream write(&writeFile);//写入文件
    QStringList privilegelist;
    QStringList list;
    QString privilege;
    QString str;
    QString str1;
    privilege=keywordList[1];
    privilegelist=privilege.split(",");//将权限以逗号分隔
    qDebug()<<"privilegelist="<<privilegelist;
    int flag;
    while(!read.atEnd()){
        flag=0;
        str=read.readLine();//读取一行
        list=str.split(",");//将一行以逗号分隔
        qDebug()<<"list="<<list;
        for(int i=0;i<userlist.size();i++){
            for(int i=0;i<privilegelist.size();i++){
                if(privilegelist[i]=="create"){//创建
                    list[1]="0";//将权限设置为0
                }
                else if(privilegelist[i]=="drop"){//删除
                    list[2]="0";//将权限设置为0
                }
                else if(privilegelist[i]=="update"){//更新
                    list[3]="0";//将权限设置为0
                }
                else if(privilegelist[i]=="insert"){//插入
                    list[4]="0";//将权限设置为0
                }
                else if(privilegelist[i]=="delete"){//删除
                    list[5]="0";//将权限设置为0
                }
            }
            if(list[0]==userlist[i]){//如果用户名相同
                //将权限写入文件
                str1=list[0]+","+list[1]+","+list[2]+","+list[3]+","+list[4]+","+list[5];
                flag=1;
            }

        }
        qDebug()<<"grant:str="<<str;
        qDebug()<<"grant:str1="<<str1;
        if(flag==1){
            write<<str1<<"\n";
        }
        else{
            write<<str<<"\n";
        }
    }
    QMessageBox::information(0,"提示","回收成功",
                        QMessageBox::Ok|QMessageBox::Default,
                        QMessageBox::Cancel|QMessageBox::Escape,0);
    readFile.close();//关闭文件
    readFile.remove();//删除文件
    writeFile.close();//关闭文件
    writeFile.rename(tPath);//重命名文件

}
