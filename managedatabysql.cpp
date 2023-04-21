
//通过权限管理判断是否有权限进行数据操作
#include "managedatabysql.h"
#include "qmessagebox.h"
#include "qdebug.h"
#include "privilegemanager.h"
#include "tablemanager.h"
#include "dataoperation.h"
#include "QFileDialog"
#include "iostream"
#include "fstream"
#include "sstream"
#include "QTimer"
#include "QDateTime"

managedatabysql::managedatabysql() {
    initDir();

}
//初始化文件路径
void managedatabysql::initDir() {
    QDir *dir=new QDir(QDir::currentPath());
    dir->cdUp();
    QFile file(dir->path()+"/DBMS/data/sys/curuse.txt");//打开当前用户文件
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString str=read.readLine();
    list=str.split(",");
    userName=list[0];//获取当前用户名
    dbName=list[1];//获取当前数据库名
    dirPath=dir->path()+"/DBMS/data/"+dbName;//获取当前数据库路径
    qDebug()<<dirPath;
    file.close();
}
//插入数据
void managedatabysql::insertData(QStringList keywordList) {
    privilegemanager ifmdt;
    if(ifmdt.adt(keywordList[2],userName)) {
        if ((keywordList[1] == "") ||
            (keywordList[2] == "") ||
            (keywordList[3] == "")) {
            QMessageBox::critical(0, "错误", "请检查基本信息是否正确", QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);

            return;
        }
        //表路径
        tablePath = dirPath + "/table/" + keywordList[2] + "/" + keywordList[2] + ".trd";//获取表路径
        qDebug() << "表路径" << tablePath;
        QFile file(tablePath);
        if (!file.open(QIODevice::ReadOnly | QIODevice::Text | QIODevice::Append)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream write(&file);
        QString insertInfo = "";
        QString data;
        QStringList datalist;
        data = keywordList[3];
        datalist = data.split(",");
        data = "";
        for (int i = 0; i < datalist.size(); i++) {
            if (datalist[i] == "null") {
                datalist[i] = "";
            }
            if (i < datalist.size() - 1) {//如果不是最后一个元素
                data += datalist[i] + ",";
            } else if (i == datalist.size() - 1) {//如果是最后一个元素
                data += datalist[i];
            }
        }
        qDebug() << "data" << data;
        if (datalist.size() == countfield(keywordList[2])) {//字段数目相同
            dataoperation dto;
            QString tablePath = dirPath + "/table/" + keywordList[2] + "/" + keywordList[2] + ".tdf";
            qDebug() << "表路径" << tablePath;
            QFile tablefile(tablePath);
            if (!tablefile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                qDebug() << "文件打开失败";
                return;
            }
            QTextStream readcon(&tablefile);
            QStringList conlist;
            QString readinfo;
            int flag = 0;
            for (int j = 0; j < datalist.size(); j++) {
                readinfo = readcon.readLine();
                conlist = readinfo.split(",");
                if (conlist[1] == "number" && !dto.isDigitString(datalist[j])) {
                    flag = 1;
                } else if (conlist[1] == "date" & !dto.isDateString(datalist[j])) {
                    flag = 1;
                } else if (conlist[3] == "非空" && datalist[j] == NULL) {
                    flag = 3;
                } else if (conlist[2] == "主键" && hassame(j, datalist[j])) {
                    flag = 2;
                }
            }
            qDebug() << "flag=" << flag;
            if (flag == 0) {
                insertInfo += data + "\n";
                write << insertInfo;
                writeintoLOG(0, keywordList);
                qDebug() << "插入成功";
            } else if (flag == 1) {
                QMessageBox::critical(0, "错误", "数据类型不匹配", QMessageBox::Ok | QMessageBox::Default,
                                      QMessageBox::Cancel | QMessageBox::Escape, 0);
            } else if (flag == 2) {
                QMessageBox::critical(0, "错误", "主键重复", QMessageBox::Ok | QMessageBox::Default,
                                      QMessageBox::Cancel | QMessageBox::Escape, 0);
            } else if (flag == 3) {
                QMessageBox::critical(0, "错误", "非空字段不能为空", QMessageBox::Ok | QMessageBox::Default,
                                      QMessageBox::Cancel | QMessageBox::Escape, 0);
            }
        } else {
            QMessageBox::critical(0, "错误", "字段数目不匹配,请检查插入数据个数！",
                                  QMessageBox::Ok | QMessageBox::Default, QMessageBox::Cancel | QMessageBox::Escape, 0);
        }
        file.close();
    }
    else{
        QMessageBox::critical(0, "错误", "无插入数据权限", QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }

}

void managedatabysql::deleteData(QStringList  keywordList) {
    privilegemanager ifmdt;//权限管理
    if(ifmdt.ddt(keywordList[1],userName)){
        if ((keywordList[1])==""||(keywordList[2])=="") {
            QMessageBox::critical(0, "错误", "请检查基本信息是否正确", QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }
        QString fieldPath= dirPath + "/table/" + keywordList[1] + "/" + keywordList[1] + ".tdf";
        /*
         * classno,varchar,主键,非空
            classname,varchar,非主键,非空
            credit,number,非主键,非空
         */
        qDebug()<<"字段路径"<<fieldPath;
        tablePath = dirPath + "/table/" + keywordList[1] + "/" + keywordList[1] + ".trd";//获取表数据路径
        /*
         *111111,Java,3
            222222,C++,3
            333333,数据库,3
         */
        qDebug()<<"表路径"<<tablePath;
        QFile readFile(tablePath);
        QFile fieldFile(fieldPath);
        if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败";
            return;
        }
        if(!fieldFile.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败";
            return;
        }
        QTextStream read(&readFile);
        QTextStream readfield(&fieldFile);
        QString afterDelPath=dirPath + "/table/"+keywordList[1]+"/del.trd";
        QFile writeFile(afterDelPath);
        if (!writeFile.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败！";
            return;
        }
        QTextStream write (&writeFile);
        QStringList list;
        QStringList datalist;
        QStringList delline;
        QString str,delfield,data,delInfo;

        delfield=keywordList[2];

        int deleColId=0;//删除列的id
        while(!readfield.atEnd()){
            str=readfield.readLine();
            list=str.split(",");//逐行读取找要删除的字段
            if(list[0]==delfield){//list[0]为字段名,diefield为要删除的字段名
                qDebug()<<"找到删除列"<<"deleColId="<<deleColId;
                while(!read.atEnd()){
                    data=read.readLine();
                    datalist=data.split(",");
                    if(datalist[deleColId]==keywordList[4]){
                        delline=datalist;
                        for (int i = 0; i < delline.size(); i++) {
                            if (i < delline.size() - 1) {//如果不是最后一个元素
                                delInfo += delline[i] + ",";
                            } else if (i == delline.size() - 1) {//如果是最后一个元素
                                delInfo += delline[i];
                            }
                        }

                        }else{
                            write<<data+"\n";
                        }
                    }
                }else{
                    deleColId++;
                }
            }
        writeintoLOG(1,keywordList);
        fieldFile.close();
        readFile.close();
        readFile.remove();
        writeFile.close();
        writeFile.rename(tablePath);
        }
    else{
        QMessageBox::critical(0, "错误", "无删除数据权限", QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);


    }

}

void managedatabysql::updateData(QStringList keywordList) {
     privilegemanager ifmdt;//权限管理
    if(ifmdt.mdt(keywordList[1],userName)){
        if ((keywordList[1]=="")||keywordList[2]=="") {//keywordList[1]为表名，keywordList[2]为字段名
            QMessageBox::critical(0, "错误", "请检查基本信息是否正确", QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }
        QString fieldPath= dirPath + "/table/" + keywordList[1] + "/" + keywordList[1] + ".tdf";
        /*
         * classno,varchar,主键,非空
            classname,varchar,非主键,非空
            credit,number,非主键,非空
         */
        qDebug()<<"字段路径"<<fieldPath;
        tablePath = dirPath + "/table/" + keywordList[1] + "/" + keywordList[1] + ".trd";//获取表数据路径
        /*
         *111111,Java,3
            222222,C++,3
            333333,数据库,3
         */
        qDebug()<<"表路径"<<tablePath;
        QFile readFile(tablePath);
        QFile fieldFile(fieldPath);
        if(!readFile.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败";
            return;
        }
        if(!fieldFile.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败";
            return;
        }
        QString str0;
        QStringList list0;
        QTextStream updatedata(&fieldFile);
        QString updatefield=keywordList[2];
        int update=0;
        while(!updatedata.atEnd()){
            str0=updatedata.readLine();
            list0=str0.split(",");
            if(list0[0]==updatefield){
                qDebug()<<"找到更新列"<<update;
                updateColId=update;
            }else{
                update++;
            }
        }
        fieldFile.close();
        QTextStream read(&readFile);
        QTextStream readfield(&fieldFile);
        QString afterDelPath=dirPath + "/table/"+keywordList[1]+"/del.trd";
        QFile writeFile(afterDelPath);
        if (!writeFile.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败！";
            return;
        }
        QTextStream write (&writeFile);
        QStringList list;
        QStringList datalist;
        QStringList updateline;
        QString str,fofield,data,updateInfo;
        fofield=keywordList[4];//keywordList[4]为要更新的字段值
        int foColId=0;//更新列的id
        while(!readfield.atEnd()){
            str=readfield.readLine();
            list=str.split(",");//逐行读取找要更新的字段
            if(list[0]==fofield){//list[0]为字段名,fofield为要更新的字段名
                qDebug()<<"找到更新列"<<"foColId="<<foColId;
                while(!read.atEnd()){
                    data=read.readLine();
                    datalist=data.split(",");
                    if(datalist[foColId]==keywordList[6]){//keywordList[6]为更新前的值
                        updateline=datalist;
                        updateInfo="";
                        for (int i = 0; i < updateline.size(); i++) {
                            if (i < updateline.size() - 1) {
                                if (i == updateColId) {//如果i等于updateColId,则将更新后的值写入
                                    updateInfo = updateInfo + keywordList[3] +",";
                                }//keywordList[3]为更新后的值
                                else {//如果i不能等于updateColId,则直接将原来的值写入
                                    updateInfo = updateInfo + updateline[i] + ",";
                                }
                            }
                            else if (i == updateline.size() - 1) {
                                if (i == updateColId) {
                                    updateInfo = updateInfo + keywordList[3];
                                }
                                else {
                                    updateInfo = updateInfo + updateline[i];
                                }
                            }
                            qDebug() << "updateInfo=" << updateInfo;
                        }
                        write<<updateInfo+"\n";
                        }else{
                            write<<data+"\n";
                        }
                    }
                }else{
                    foColId++;
                }
            }
        //写入日志

        writeintoLOG(2,keywordList);
        fieldFile.close();
        readFile.close();
        readFile.remove();
        writeFile.close();
        writeFile.rename(tablePath);
        }else{
        QMessageBox::critical(0, "错误", "无更新数据权限", QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
    }

//写入日志
void managedatabysql::writeintoLOG(int i, QStringList keywordList) {

    QDir * dir =new QDir(QDir::currentPath());
    dir->cdUp();
    QString fileNmae=dir->path()+"/DBMS/log/sys.txt";
    QFile file(fileNmae);
    QDateTime dateTime = QDateTime::currentDateTime();//获取系统现在的时间
    if (!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        qDebug()<<"文件打开失败！";
        QMessageBox::warning(NULL,"警告","文件打开失败！",QMessageBox::Yes|QMessageBox::No,QMessageBox::Yes);
        return;
    }
    QTextStream streamFile(&file);
    if(i==0){//向表中插入数据记录入日志文件
        streamFile <<dbName<<"|"<<userName<<"|"<<dateTime.toString("yyyyy-MM-dd hh:mm:ss")<<"|"<<"insert into "<<keywordList[2]<<"values "<<keywordList[3]<<");"<<endl;

    }

}

//计算属性个数
int managedatabysql::countfield(QString tableName) {
    QString tableP=dirPath + "/table/" + tableName + "/" + tableName + ".tdf";
    QFile tablef(tableP);
    if (!tablef.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败！";
        return 0;
    }
    QTextStream readt(&tablef);
    QString readi;
    int n=0;
    while(!readt.atEnd()){
        readi=readt.readLine();
        n++;//计算属性个数
    }
    tablef.close();
    return n;
}

bool managedatabysql::hassame(int i, QString str) {
    int flag=0;
    qDebug()<<tablePath;
    QFile datafile(tablePath);
    if (!datafile.open(QIODevice::ReadOnly|QIODevice::Text)){
        qDebug()<<"文件打开失败！";
        return false;
    }
    QTextStream readdata(&datafile);
    QStringList list;
    QString string;
    while(!readdata.atEnd()){
        string=readdata.readLine();
        list=string.split(",");
        if(list[i]==str){
            flag=1;

        }
    }
    datafile.close();
    if(flag==1){
        return true;
    }else{
        return false;
    }

}


