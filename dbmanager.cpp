//
// Created by lx on 2023/4/6.
//
#include"qdir.h"//qdir类的主要作用：创建目录、删除目录、重命名目录、判断目录是否存在、获取目录下的文件列表等
#include "dbmanager.h"
#include "selectdatabase.h"
#include "login.h"
#include "qdebug.h"
#include "qmessagebox.h"//qmessagebox类的主要作用：显示消息框
#include "qfile.h"//qfile类的主要作用：读写文件、判断文件是否存在、获取文件大小、获取文件名、获取文件路径等

dbmanager::dbmanager() {//构造函数
    QDir *dir = new QDir(QDir::currentPath());//获取当前路径
    dir->cdUp();//返回上一级目录
    path =dir->path()+"/DBMS/data/";//数据库文件路径
}

void dbmanager::myCreateDataBase(QString dbname) {//创建用户数据库
    qDebug()<<dbname;
    QDir *dir1 = new QDir(QDir::currentPath());//创建QDir对象
    dir1->cdUp();//返回上一级目录
    dataPath=path+dbname;//数据文件路径
    QDir dir(dataPath);//创建QDir对象

    if(dir.exists()){//判断数据库是否存在
        qDebug()<<"数据库已存在，数据库创建失败！";
        QMessageBox::warning(NULL,
                             "警告",
                             "数据库已存在,创建数据库失败",
                             QMessageBox::Yes|QMessageBox::No,
                             QMessageBox::Yes);//显示警告对话框
        return;
    }
    else {//数据库不存在
        dir.mkpath(dataPath);//创建数据库文件夹
        QMessageBox::information(NULL,
                                 "提示",
                                 "数据库创建成功",
                                 QMessageBox::Yes|QMessageBox::No,
                                 QMessageBox::Yes);//显示提示对话框
        qDebug()<<dataPath;
        qDebug()<<"数据库创建成功！";

        //创建表文件夹
        QString tablePath=dataPath+"/table";//表文件路径
        QDir dir1(tablePath);//创建QDir对象
        if(!dir1.exists()){//判断表文件夹是否存在
            dir1.mkpath(tablePath);//创建表文件夹
            qDebug()<<"表文件夹创建成功！";
        }
        else{
            qDebug()<<"表文件夹已存在！";
        }

        //视图文件夹创立
        QString viewPath=dataPath+"/view";//视图文件路径
        QDir dir2(viewPath);//创建QDir对象
        if(!dir2.exists()){//判断视图文件夹是否存在
            dir2.mkpath(viewPath);//创建视图文件夹
            qDebug()<<"视图文件夹创建成功！";
        }
        else{
            qDebug()<<"视图文件夹已存在！";
        }

        //索引文件夹创立---->后期可实现


        //用户信息文件创建
        QString userin =path+dbname+"/userinfor.txt";//用户信息文件路径
        QFile userfile(userin);//创建QFile对象
        if(!userfile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append))
            //writeonly:只写方式打开文件，如果文件不存在则创建，如果文件存在则清空文件内容
            //text:以文本方式打开文件
            //append:以追加方式打开文件
        {
            qDebug()<<"文件打开失败, 用户信息文件创建失败！";
            return;
        }
        QTextStream outu(&userfile);//创建QTextStream对象
        QString adminpath=path+"sys/admin.txt";//管理员信息文件路径
        QFile adminfile(adminpath);//创建QFile对象
        if(!adminfile.open(QIODevice::ReadOnly)){//readonly:只读方式打开文件
            qDebug()<<"文件打开失败, 管理员信息文件打开失败！";
            return;
        }

        QTextStream reada(&adminfile);//创建QTextStream对象
        QString adminuser=reada.readLine();//读取管理员用户名
        while(!adminuser.isNull()){//判断是否读到文件末尾
            outu<<adminuser<<endl;//写入用户名
            adminuser=reada.readLine();//读取管理员用户名
        }
        adminfile.close();//关闭文件
        userfile.close();//关闭文件
        //用户权限文件创立
        QString  userpri =path+dbname+"/userprivilege.txt";//用户权限文件路径
        QFile  userprifile(userpri);//创建QFile对象
        if(!userprifile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
            qDebug()<<"文件打开失败, 用户权限文件创建失败！";
            return;
        }

        //数据存入结构体databae中
        database my_database;
        char *pre =dbname.toLatin1().data();//toLatin1()函数的作用：将QString转换为char*,data()函数的作用：将QByteArray转换为char*
        memcpy(my_database.daname,pre,128);//将数据库名存入结构体中
        my_database.crtime=QDateTime::currentDateTime();//获取当前时间
        char *pre2=dataPath.toLatin1().data();
        //memcpy()函数的作用：将内存区域src中的前count个字节复制到内存区域dest中
        memcpy(my_database.filename,pre2,256);//将数据库路径存入结构体中
        my_database.type=true;//数据库类型为用户数据库
        //

        //创建基本信息文件
        QFile file01(dataPath+"/"+dbname+".db");//创建QFile对象
        if(!file01.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug()<<"文件打开失败, 基本信息文件创建失败！";
            return;
        }
        QTextStream out(&file01);//创建QTextStream对象
        out<<"NAME:"+dbname+"\n";
        out<<"TYPE:用户\n";
        out<<"FILENAME:"+dataPath+"\n";
        out<<"CREATETIME:"+(my_database.crtime).toString("yyyy-mm-dd hh.mm.ss")+"\n";
        file01.close();//关闭文件


    }
}

void dbmanager::myDeleteDataBase(QString dbname) {
    qDebug()<<dbname;
    dataPath=path+"/"+dbname;//数据文件路径
    QDir dir(dataPath);//创建QDir对象

    if(dir.exists()){
        dir.removeRecursively();//删除数据库文件夹
        QMessageBox::information(NULL,
                                 "提示",
                                 "数据库删除成功!",
                                 QMessageBox::Yes|QMessageBox::No,
                                 QMessageBox::Yes);//显示提示对话框
        qDebug()<<"数据库删除成功！";
    }else{
        qDebug()<<"数据库不存在，删除失败！";
        QMessageBox::warning(NULL,
                             "警告",
                             "数据库不存在,删除数据库失败",
                             QMessageBox::Yes|QMessageBox::No,
                             QMessageBox::Yes);//显示警告对话框
        return ;
    }

}



//将创建数据库日志写入文件
void dbmanager::writedelDBinto(QString dataname) {
    //初始化系统目录
    QDir *dir =new QDir(QDir::currentPath());//创建QDir对象
    dir->cdUp();//返回上一级目录
    QString fileName =dir->path()+"/DBMS/log/sys.txt";//系统文件路径
    QFile file(fileName);//创建QFile对象
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append)){
        qDebug()<<"打开文件失败";
        QMessageBox::warning(NULL,
                             "警告！",
                             "打开文件失败！",
                             QMessageBox::Yes|QMessageBox::No,
                             QMessageBox::Yes);//显示警告对话框
        return;
    }
    QTextStream streamFile(&file);//创建QTextStream对象
    streamFile<<endl;
    extern QString name;//extern关键字的作用：声明一个全局变量
    streamFile<<name<<"delete database "<<dataname<<" at "<<QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")<<endl;
    file.close();//关闭文件

}

void dbmanager::writeDBinto(struct dataBase my_database) {
    // 初始化系统目录
    QDir *dir = new QDir(QDir::currentPath());

    dir->cdUp();
    QString fileName = dir->path() + "/DBMS/log/sys.txt";
    QFile   file(fileName);

    if (!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
    {
        QMessageBox::warning(NULL,
                             "警告！",
                             "打开文件失败！",
                             QMessageBox::Yes | QMessageBox::No,
                             QMessageBox::Yes);
    }
    QTextStream streamFile(&file);

    streamFile << endl;
    extern QString name;
    streamFile << name << "create " << my_database.daname << " dataBase ";
    streamFile << "filepath: " << my_database.filename << " " <<
               my_database.crtime.toString("yyyy-MM-dd hh:mm:ss") << endl;
    file.close();


}
