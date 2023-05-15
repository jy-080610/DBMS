
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
    dirPath = dir->path() + "/DBMS/data/" + list[1];//获取当前数据库路径
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
        tablePath = dirPath + "/table/" + keywordList[2] + "/" +keywordList[2] + ".trd";        qDebug() << "表路径" << tablePath;
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
            QString tablePath=dirPath+"/table/"+keywordList[2]+"/"+keywordList[2]+".tdf";
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
void managedatabysql::deleteData(QStringList keywordList) {
    privilegemanager ifmdt;

    if (ifmdt.ddt(keywordList[1], userName)) {
        if ((keywordList[1] == "") ||
            (keywordList[2] == "")) {
            QMessageBox::critical(0, "错误", "请检查基本信息是否正确",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }


        QString fieldPath = dirPath + "/table/" + keywordList[1] + "/" +
                            keywordList[1] + ".tdf";
        //         * classno,varchar,主键,非空
//            classname,varchar,非主键,非空
//            credit,number,非主键,非空
//         */
        tablePath = dirPath + "/table/" + keywordList[1] + "/" +
                    keywordList[1] + ".trd";
        //         *111111,Java,3
//            222222,C++,3
//            333333,数据库,3
//         */
        qDebug() << "当前字段的路径为：" + fieldPath;
        qDebug() << "当前数据的路径为：" + tablePath;
        QFile readFile(tablePath);
        QFile fieldFile(fieldPath);

        if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }

        if (!fieldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream read(&readFile);
        QTextStream readfield(&fieldFile);

        QString afterDelPath = dirPath + "/table/" + keywordList[1] +
                               "/del.trd";
        QFile writeFile(afterDelPath);

        if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream write(&writeFile);
        QStringList list, datalist, delline;
        QString     str, delfield, data, delInfo;

        delfield = keywordList[2];

        // 要删除的那一列的列号
        int deleColId = 0;

        while (!readfield.atEnd()) {
            str = readfield.readLine();
            list = str.split(",");

            if (list[0] == delfield) {
                qDebug() << "delecolid=" << deleColId;

                while (!read.atEnd()) {
                    data = read.readLine();
                    datalist = data.split(",");

                    if (datalist[deleColId] == keywordList[4]) {
                        delline = datalist;

                        for (int i = 0; i < delline.size(); i++) {
                            if (i < delline.size() - 1) {
                                delInfo = delline[i] + ",";
                            }
                            else if (i == delline.size() - 1) {
                                delInfo = delline[i];
                            }
                        }
                    }

                    else {
                        write << data + "\n";
                    }
                }
            }
            else {
                deleColId++;
            }
        }
        writeintoLOG(1, keywordList);
        fieldFile.close();
        readFile.close();
        readFile.remove();
        writeFile.close();
        writeFile.rename(tablePath);
    }
    else {
        QMessageBox::critical(0, "错误", "无删除数据权限操作！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

void managedatabysql::updateData(QStringList keywordList) {
    privilegemanager ifmdt;

    if (ifmdt.mdt(keywordList[1], userName)) {
        if ((keywordList[1] == "") ||
            (keywordList[2] == "")) {
            QMessageBox::critical(0, "错误", "请检查基本信息是否正确",
                                  QMessageBox::Ok | QMessageBox::Default,
                                  QMessageBox::Cancel | QMessageBox::Escape, 0);
            return;
        }
        QString fieldPath = dirPath + "/table/" + keywordList[1] + "/" +
                            keywordList[1] + ".tdf";
        /*
         * classno,varchar,主键,非空
            classname,varchar,非主键,非空
            credit,number,非主键,非空
         */
        qDebug() << "字段路径" << fieldPath;
        tablePath = dirPath + "/table/" + keywordList[1] + "/" + keywordList[1] + ".trd";
        /*
         *111111,Java,3
            222222,C++,3
            333333,数据库,3
         */
        qDebug() << "表路径" << tablePath;
        qDebug() << "当前字段的路径为：" + fieldPath;
        qDebug() << "当前数据的路径为：" + tablePath;
        QFile readFile(tablePath);
        QFile fieldFile(fieldPath);

        if (!readFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }

        if (!fieldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }

        QString str0;
        QStringList list0;
        QTextStream updatedata(&fieldFile);
        QString updatefield = keywordList[2];
        int update = 0;

        while (!updatedata.atEnd()) {
            str0 = updatedata.readLine();
            list0 = str0.split(",");

            if (list0[0] == updatefield) {
                qDebug() << "updatecolid=" << update;
                updateColId = update;
            } else {
                update++;
            }
        }
        fieldFile.close();

        if (!fieldFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }

        QTextStream read(&readFile);
        QTextStream readfield(&fieldFile);

        QString afterDelPath = dirPath + "/table/" + keywordList[1] +
                               "/del.trd";
        QFile writeFile(afterDelPath);

        if (!writeFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "文件打开失败";
            return;
        }
        QTextStream write(&writeFile);
        QStringList list, datalist, updateline;
        QString str, fofield, data, updateInfo;

        fofield = keywordList[4];

        // 要定位行的那一列的列号
        int foColId = 0;

        while (!readfield.atEnd()) {
            str = readfield.readLine();
            list = str.split(",");

            if (list[0] == fofield) {
                qDebug() << "foid=" << foColId;

                while (!read.atEnd()) {
                    data = read.readLine();
                    datalist = data.split(",");

                    if (datalist[foColId] == keywordList[6]) {
                        updateline = datalist;
                        updateInfo = "";

                        for (int i = 0; i < updateline.size(); i++) {
                            if (i < updateline.size() - 1) {
                                if (i == updateColId) {
                                    updateInfo = updateInfo + keywordList[3] + ",";
                                } else {
                                    updateInfo = updateInfo + updateline[i] + ",";
                                }
                            } else if (i == updateline.size() - 1) {
                                if (i == updateColId) {
                                    updateInfo = updateInfo + keywordList[3];
                                } else {
                                    updateInfo = updateInfo + updateline[i];
                                }
                            }
                            qDebug() << "updateInfo=" << updateInfo;
                        }
                        qDebug() << "updateInfo=" << updateInfo;
                        write << updateInfo + "\n";
                    } else {
                        write << data + "\n";
                    }
                }
            } else {
                foColId++;
            }
        }
        writeintoLOG(2, keywordList); //    写入日志
        fieldFile.close();
        readFile.close();
        readFile.remove();
        writeFile.close();
        writeFile.rename(tablePath);
    } else {
        QMessageBox::critical(0, "错误", "无修改数据权限操作！",
                              QMessageBox::Ok | QMessageBox::Default,
                              QMessageBox::Cancel | QMessageBox::Escape, 0);
    }
}

//写入日志
void managedatabysql::writeintoLOG(int i, QStringList keywordList) {

    QDir *dir = new QDir(QDir::currentPath());
    dir->cdUp();
    QString fileName = dir->path() + "/DBMS/log/sys.txt";
    QFile   file(fileName);
    QDateTime dateTime;
    dateTime = QDateTime::currentDateTime();

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QMessageBox::warning(NULL,
                             "警告！",
                             "错误！",
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);
    }
    QTextStream streamFile(&file);

    if (i == 0) {
        streamFile << dbName << "|" << userName << "|" <<
                   dateTime.toString("yyyy-MM-dd hh:mm:ss") << "|" << "insert into " <<
                   keywordList[2] << " values(" << keywordList[3] << ");" << endl;
    }
    else if (i == 1) {
        streamFile << dbName << "|" << userName << "|" <<
                   dateTime.toString("yyyy-MM-dd hh:mm:ss") << "|" << "delete from " <<
                   keywordList[1] << " where " << keywordList[2] << keywordList[3] <<
                   keywordList[4] << ";" << endl;
    }
    else {
        streamFile << dbName << "|" << userName << "|" <<
                   dateTime.toString("yyyy-MM-dd hh:mm:ss") << "|" << "update " <<
                   keywordList[1] << " set " << keywordList[2] << "=" << keywordList[3]
                   << " where " << keywordList[4] << keywordList[5] <<
                   keywordList[6] << ";" << endl;
    }
    file.close();

}

//计算属性个数
int managedatabysql::countfield(QString tablename) {
    //字段数
    QString tableP = dirPath + "/table/" + tablename + "/" + tablename + ".tdf";
    qDebug() << tableP;
    QFile tablef(tableP);
    if (!tablef.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "文件打开失败！";
    }
    QTextStream readt(&tablef);
    QString     readi;
    int n=0;
    while (!readt.atEnd()) {
        readi = readt.readLine();
        n++;
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


