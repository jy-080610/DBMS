//
// Created by Asus on 2023/4/17.
//

#ifndef DBMS_INDEXMANAGER_H
#define DBMS_INDEXMANAGER_H
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>//unistd.h是POSIX操作系统API的头文件，提供对POSIX操作系统API的访问功能
#include<QString>
#include<iostream>
#define M 3//B+树的阶数
#define QUANEUE_LEN 100//B+树的最大关键字数
using namespace std;

#define MALLOC_NODE(p, type) type *p = (type *)malloc(sizeof(type)); memset(p,      \
                                                                            0,      \
                                                                            sizeof( \
                                                                                type))
#define FREE_NODE(p) free(p)//释放内存空间
#define FSEEK_END_WRITE(fp,pos,buf,size)fseek(fp,0,SEEK_END); \
                                                             pos=ftell(fp);fwrite(buf,size,1,fp)//将buf写入文件fp中
#define FSEEK_HED_WRITE(fp,pos,buf,size)fseek(fp,pos,SEEK_SET); \
                                                                pos=ftell(fp);fwrite(buf,size,1,fp)//将buf写入文件fp中
#define FSEEK_FIXED_READ(fp,pos,buf,size)fseek(fp,pos,SEEK_SET); \
                                                                 fread(buf,size,1,fp)//从文件fp中读取数据到buf中
#define FSEEK_FIXED_WRITE(fp,pos,buf,size)fseek(fp,pos,SEEK_SET); \
                                                                  fwrite(buf,size,1,fp)//将buf写入文件fp中
#define OPEN_FILE(file_name,mode) fopen(file_name,mode)//打开文件
#define CLOSE_FILE(fp)fclose(fp)//关闭文件
#define OPEN_FILE_READ(file_name,mode,buf,size) fp =OPEN_FILE(file_name,mode);fread(buf,size,1,fp);//打开文件并读取数据到buf中
#define OPEN_FILE_WRITE(file_name,mode,buf,size) fp =OPEN_FILE(file_name,mode);fwrite(buf,size,1,fp);//打开文件并将buf写入文件中
typedef unsigned int unit;//定义一个无符号整型变量
typedef unsigned short int sint;//定义一个无符号短整型变量
typedef FILE *file;//定义一个文件指针
typedef unsigned long long ull;//定义一个无符号长整型变量
//定义数据结构
typedef struct {
    sint len;//数据长度
    unit pos;//数据位置
} _data;//数据结构
//文件头结构体
typedef struct {
  unit head;//文件头位置
  unit node;//节点数目
} FileHead;//文件头结构体
//索引节点结构体
typedef struct {
    sint keyNum;//关键字数目
    unit parent;//父节点位置
    ull key[M+1];//关键字-索引值
    unit ptr[M+1];//节点位置
    _data data[M+1];//数据信息
} BTNode;//索引节点结构体
//存储查找结果
typedef struct {
   sint leng;
   unit pt;//指向找到的节点位置
   sint i;//1，，，m在结点中的关键字序号
    sint tag;//1表示找到，0表示未找到
} Result;


typedef struct {
    char NAME[128];//表名
    bool unique;//是否唯一
    bool asc;//是否升序
    int file_num;//文件数目
    char fields[128][2];//字段名
    char record_file[256];//记录文件名
    char index_file[256];//索引文件名
} index_desc;//索引描述符
class Indexmanager {

public:
    /* 查询语句使用时
       1.  Indexmanager* idmg=new Indexmanager(QString tablename)
       2.  idmg.checkindex(QString finame1,QString finame2)
       查看含有该字段组的索引文件名，如果没有该索引，则返回NULL
       3.  idmg.SelectBtree(QString index_name,QString keyvalues)
       index_name为2中返回的索引名，keyvalues为关键字对应的值
       4.  imdg.searesult
       查找结果存在searesult中
       形式为"values1,values2"，若未找到相应值，则searesult值为"未查到相应结果"*/
    Indexmanager();
    Indexmanager(QString tablename);
    void createFalseIndex(QStringList keyword);
    int Search(BTNode * NodeBuf,ull key);//根据键值查找
    void SearchBTree(unit node_pos,
                     ull key,
                     Result *r);//在B+树中查找
    void upFileHead(unit new_head_pos);//更新头结点的信息
    void newRoot(unit head_pos,
                 ull key,
                 _data data,
                 unit ap);//新建根节点
    unit split(BTNode *NodeBuf,
               unit node_pos,
               sint s);//分裂节点
    BTNode Insert(unit node_pos,
                  sint i,
                  ull key,
                  uint ap,
                  _data data);//插入关键字
    void InsertBTree(unit head_pos,
                     ull key,
                     unit node_pos,
                     sint i,
                     _data data);//插入关键字
    void insertData(char *con,ull key);//插入数据
    ull hashkey(string s);//哈希函数
    void SelectBtree(QString index_name,QString keyvalues);//查找
    void deleteIndex(QString index_name);//删除索引
    QString checkindex(QString finame1,QString finame2);//查看是否有该索引
    QString searesult;//查找结果
private:
    QString dirPath;//文件夹路径
    QString indexPath;//索引文件路径
    QString datafile;//数据文件路径
    QString indexfile;//索引文件路径
    QString tablefile;//表文件路径
    QString recordfile;//记录文件路径
    QString indexrecordfile;//索引记录文件路径
    file fp;//文件指针


//查询结果字符串
ull mod=1e9+7;//1e9+7为一个大素数
ull h[100010];//哈希值
ull prime=233317;
};


#endif //DBMS_INDEXMANAGER_H
