//
// 索引管理
//

#include <QStringList>
#include "indexmanager.h"
#include "qdir.h"
#include"string"
#include<string>
#include <QMessageBox>
#include"qdebug.h"

Indexmanager::Indexmanager() {

}

Indexmanager::Indexmanager(QString tablename) {
    QDir *dir = new QDir(QDir::currentPath());//获取当前路径
    searesult="未查找到相应结果";
    dir->cdUp();//返回上一级目录
    QFile file(dir->path() + "/DBMS/data/sys/curuse.txt");//打开索引文件
    if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        qDebug()<<"打开失败";
    }
    QTextStream read(&file);
    QStringList list;
    QString str =read.readLine();//读取一行
    qDebug()<<"用户信息"+str;
    list=str.split(",");
    QString userName=list[0];//获取用户名
    QString dbName=list[1];//获取数据库名
    dirPath=dir->path()+"DBMS/data/"+list[1];
    file.close();
    tablefile=dirPath+"/table/"+tablename+"/"+tablename+".tdf";//字段文件
    recordfile=dirPath+"/table/"+tablename+"/"+tablename+".trd";//记录文件
    indexrecordfile=dirPath+"/table/"+tablename+"/"+tablename+".tid";//索引记录文件
    dirPath=dirPath+"/table/"+tablename+"/";//表文件夹路径

}

int Indexmanager::Search(BTNode *NodeBuf, ull key) {
    sint i=1;
    while(i<=NodeBuf->keyNum&&key>NodeBuf->key[i]){
        i++;
    }

    return i;
}

void Indexmanager::SearchBTree(unit node_pos, ull key, Result *r) {

    sint i=0;
    sint found=0;//是否找到
    unit parent_pos=0;//父节点位置
    _data temp;//临时数据
    MALLOC_NODE( NodeBuf, BTNode );//申请节点空间

    while(node_pos!=0&&found==0){
        FSEEK_FIXED_READ(fp,node_pos,NodeBuf, sizeof(BTNode));//读取节点
        i=Search(NodeBuf,key);//查找
        if(i<=NodeBuf->keyNum&&NodeBuf->key[i]==key){
            found=1;
        }else{
            parent_pos=node_pos;
            node_pos=NodeBuf->ptr[i-1];//指向子节点
        }
    }
    if (1==found){
        r->pt=node_pos;
        r->i=i;//记录位置
        r->tag=1;//标记为找到
        temp = NodeBuf->data[i];//获取数据
        qDebug()<<temp.pos;
        MALLOC_NODE(aaa,char);
        qDebug()<<temp.len;
        file mm = OPEN_FILE(datafile.toLatin1().data(),"rb");//打开数据文件
        FSEEK_FIXED_READ(mm,temp.pos,aaa,temp.len);//读取数据
        searesult=QString::fromStdString(aaa);//转换为QString
        qDebug()<<searesult;
        FREE_NODE(aaa);
        CLOSE_FILE(mm);
        FREE_NODE(NodeBuf);//释放节点空间
        return;
    }else{
        r->pt=parent_pos;
        r->i=i;
        r->tag=0;
        qDebug()<<"未找到相应值";
    }
    FREE_NODE(NodeBuf);//释放节点空间


}

void Indexmanager::upFileHead(unit new_head_pos) {//更新文件头

    MALLOC_NODE(fileHeadBuf,FileHead);//申请文件头空间
    FSEEK_FIXED_READ( fp, 0, fileHeadBuf, sizeof(FileHead) );
    if ( new_head_pos > 0 )//如果新的头位置大于0
    {
        fileHeadBuf->head = new_head_pos;
    }
    fileHeadBuf->node++;//节点数加一
    FSEEK_FIXED_WRITE( fp, 0, fileHeadBuf, sizeof(FileHead) );
    FREE_NODE( fileHeadBuf );//释放文件头空间
}

void Indexmanager::newRoot(unit head_pos, ull key, _data data, unit ap) {

    uint pos;//位置
    MALLOC_NODE( rootNodeBuf, BTNode );//申请节点空间
    rootNodeBuf->keyNum = 1;//关键字数为1
    rootNodeBuf->ptr[0]=head_pos;//指向原根节点
    rootNodeBuf->ptr[1]=ap;
    rootNodeBuf->key[1]=key;//插入关键字
    rootNodeBuf->data[1]=data;//插入数据

    //读取原根节点更新parent位置
    FSEEK_FIXED_READ(fp,head_pos,rootNodeBuf,sizeof(BTNode));//写入节点
    rootNodeBuf->parent=pos;
    FSEEK_END_WRITE(fp,head_pos,rootNodeBuf,sizeof(BTNode));//写入节点
    //读取分裂节点更新parent位置
    FSEEK_FIXED_READ(fp,ap,rootNodeBuf,sizeof(BTNode));//写入节点
    rootNodeBuf->parent=pos;
    FSEEK_END_WRITE(fp,ap,rootNodeBuf,sizeof(BTNode));//写入节点

    //更新文件头
    upFileHead(pos);
    FREE_NODE( rootNodeBuf );//释放节点空间
}
unit Indexmanager::split(BTNode *NodeBuf, unit node_pos, sint s) {
    sint i,j;
    sint n=NodeBuf->keyNum;//关键字数
    unit ap;//分裂节点位置
    MALLOC_NODE( apNodeBuf, BTNode );//申请节点空间
    MALLOC_NODE( apNodeBufChild, BTNode );//申请节点空间
    apNodeBuf->ptr[0]=NodeBuf->ptr[s];//指向分裂节点
    for (int i = s+1,j=1; i <=n ;i++,j++) {
        apNodeBuf->key[j]=NodeBuf->key[i];//复制关键字
        apNodeBuf->ptr[j]=NodeBuf->ptr[i];//复制指针
        apNodeBuf->data[j]=NodeBuf->data[i];//复制数据
    }
    apNodeBuf->keyNum=n-s;//分裂节点关键字数
    apNodeBuf->parent=NodeBuf->parent;//分裂节点父节点位置
    FSEEK_END_WRITE(fp,ap,apNodeBuf,sizeof(BTNode));//写入节点
    //更新分裂节点子节点的parent位置
    upFileHead(0);//更新文件头
    for (int i = 0; i <=n-s; i++) {
    if(apNodeBuf->ptr[i]!=0){
        FSEEK_FIXED_READ(fp,apNodeBuf->ptr[i],apNodeBufChild,sizeof(BTNode));
        apNodeBufChild->parent=ap;//更新parent位置
        FSEEK_END_WRITE(fp,apNodeBuf->ptr[i],apNodeBufChild,sizeof(BTNode));//写入节点
    }
    }
    FSEEK_FIXED_READ(fp,node_pos,NodeBuf,sizeof(BTNode));//写入节点
    NodeBuf->keyNum=s-1;//更新原节点关键字数
    FSEEK_END_WRITE(fp,node_pos,NodeBuf,sizeof(BTNode));//写入节点
    FREE_NODE( apNodeBuf );//释放节点空间
    FREE_NODE( apNodeBufChild );//释放节点空间
    return ap;
    }
BTNode Indexmanager::Insert(unit node_pos, sint i, ull key, uint ap, _data data) {
    BTNode  buf;
    BTNode  * NodeBuf = &buf;
    /* 读取节点 */
    FSEEK_FIXED_READ( fp, node_pos, NodeBuf, sizeof(BTNode) );

    sint j;
    for ( j = NodeBuf->keyNum; j >= i; j-- )
    {
        /* 后移 */
        NodeBuf->key[j + 1] = NodeBuf->key[j];
        NodeBuf->ptr[j + 1] = NodeBuf->ptr[j];
        NodeBuf->data[j + 1]    = NodeBuf->data[j];
    }
    NodeBuf->key[i]     = key;
    NodeBuf->ptr[i]     = ap;
    NodeBuf->data[i]    = data;

    NodeBuf->keyNum++;
    FSEEK_FIXED_WRITE( fp, node_pos, NodeBuf, sizeof(BTNode) );
    return(*NodeBuf);
}

void Indexmanager::InsertBTree(unit head_pos, ull key, unit node_pos, sint i, _data data) {
      sint s=0;
      sint finished=0;//是否完成
      sint needNewRoot=0;//是否需要新的根节点
        unit ap=0;
        BTNode NodeBuf;
        Result res;
        while(0==needNewRoot&&0==finished){
            NodeBuf=Insert(node_pos,i,key,ap,data);
            if(NodeBuf.keyNum<=M){
                finished=1;
        }else{
                //得到中间节点的位置
                s=(M+1)/2;//中间节点位置
                //分裂节点
                ap=split(&NodeBuf,node_pos,s);
                //得到父节点位置
                key=NodeBuf.key[s];
                data=NodeBuf.data[s];
                //在双亲位置插入关键字
                if(NodeBuf.parent!=0){
                    //寻找插入位置
                    node_pos=NodeBuf.parent;//父节点位置
                    FSEEK_FIXED_READ(fp,node_pos,&NodeBuf,sizeof(BTNode));//写入节点
                    i= Search(&NodeBuf,key);//寻找插入位置

                }else
                {
                    needNewRoot=1;//需要新的根节点
                }
            }
        }
        if(needNewRoot==1){
            //创建新的根节点
            newRoot(head_pos,key,data,ap);
        }

}
void Indexmanager::createFalseIndex(QStringList keyword) {
    sint node_pos;
    FileHead head;
    BTNode node;
    QString index_name=keyword[1];//索引名
    QString field_name=keyword[3];//字段名
    datafile=dirPath+index_name+".ix";
    indexfile=dirPath+index_name+".tid";

    //创建索引文件
    if ( OPEN_FILE(indexfile.toLatin1().data(), "rb" ) == NULL ){
        fp=OPEN_FILE(indexfile.toLatin1().data(), "wb+" );//创建索引文件
        //创建文件头
        FileHead head={0,1};//文件头
        FSEEK_END_WRITE(fp,node_pos,(char *)&head,sizeof(head));//写入文件头

        BTNode  node={0};
        FSEEK_END_WRITE(fp,node_pos,(char *)&node,sizeof(node));//写入节点

        head.head=node_pos;//文件头
        FSEEK_END_WRITE(fp,node_pos,(char *)&head,sizeof(head));//写入文件头
        CLOSE_FILE(fp);
    }


    //创建数据文件
    if(OPEN_FILE(datafile.toLatin1().data(),"rb")==NULL){
        fp=OPEN_FILE(datafile.toLatin1().data(),"wb");//创建数据文件
        int column=0;
        int column02=0;
        QStringList fieldlist=field_name.split(",");
        QFile tdf(tablefile);
        if(!tdf.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"打开表文件失败";
            return;
        }
        QFile ic(indexrecordfile);
        if(!ic.open(QIODevice::WriteOnly|QIODevice::Text)|QIODevice::Append){
            qDebug()<<"打开索引记录文件失败";
            return;
        }
        QTextStream streamFile(&ic);
        QTextStream check(&tdf);//读取表文件
        QString fieldrecord=check.readLine();//读取表头
        int i=0;
        while(!fieldrecord.isNull()){
            QStringList listtemp=fieldrecord.split(",");

            if (listtemp[0]==fieldlist[0]){
                column=i;
                if(listtemp[2]=="主键")
                {
                    QMessageBox::critical(NULL,"错误","索引创建错误，键值不唯一",
                                          QMessageBox::Ok|QMessageBox::Default,
                                                 QMessageBox::Cancel|QMessageBox::Escape,0);
                    qDebug()<<"索引创建错误，键值不唯一";
                    deleteIndex(index_name);
                    return;}
                    qDebug()<<listtemp[2];
                }
                if(listtemp[0]==fieldlist[1]){
                    column02=i;
                }
                i++;
                fieldrecord=check.readLine();

        }
        if(column02==0){
            QMessageBox::critical(0,"错误","索引创建错误，字段不存在",
                                 QMessageBox::Ok|QMessageBox::Default,
                                 QMessageBox::Cancel|QMessageBox::Escape,0);

       qDebug()<<"索引创建错误，字段不存在";
            deleteIndex(index_name);
            return;
        }

        streamFile<<fieldlist[0]<<","<<fieldlist[1]<<","<<index_name<<endl;
        ic.close();//关闭索引记录文件
        tdf.close();//关闭表文件
        qDebug()<<column02;
        QFile file(recordfile);
        qDebug()<<recordfile;
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)){
            qDebug()<<"打开记录文件失败";
            return;
        }
        QTextStream in(&file);
        QString line=in.readLine();
        while(!line.isNull()){//读取记录文件
            QStringList list1=line.split(",");
            string data1=list1[column].toStdString()+","+list1[column02].toStdString();

            ull key=hashkey(list1[column].toStdString());//根据关键值求哈希值
            insertData((char*)data1.data(),key);//插入数据
            line=in.readLine();//读取下一行

        }
        file.close();//关闭记录文件
        CLOSE_FILE(fp);//关闭数据文件
    }
    QMessageBox::information(0,"提示","索引创建成功",
                             QMessageBox::Ok|QMessageBox::Default,
                             QMessageBox::Cancel|QMessageBox::Escape,0);
}

void Indexmanager::insertData(char *con, ull key) {

    _data data;
    data.len=sizeof (con);
    qDebug()<<data.len;
    fp= OPEN_FILE(datafile.toLatin1().data(), "ab" );//ab+追加写入
    FSEEK_END_WRITE(fp,data.pos,con,data.len);//写入数据
    CLOSE_FILE(fp);
    //插入索引
    MALLOC_NODE(HeadBuf,FileHead);
    Result res;
    OPEN_FILE_READ( indexfile.toLatin1().data(), "rb+", HeadBuf, sizeof(FileHead) );
    SearchBTree(HeadBuf->head,key,&res);
    InsertBTree(HeadBuf->head,key,res.pt,res.i,data);
    FREE_NODE(HeadBuf);
    CLOSE_FILE(fp);

}
//生成字符串对应的哈希值
ull Indexmanager::hashkey(string s) {
    int length=s.size();
    ull temp =((ull)s[0])%mod;//mod为哈希表大小
    for (int i = 1; i < length; ++i) {
        temp=(temp*prime+((ull)s[i]))%mod;//mod为哈希表大小

    }
    return temp;
}
//查询函数利用索引
void Indexmanager::SelectBtree(QString index_name, QString keyvalues) {

    Result res;
    datafile=dirPath+index_name+".ix";
    indexfile=dirPath+index_name+".tid";
    MALLOC_NODE(HeadBuf,FileHead);
    //读取索引头
    OPEN_FILE_READ( indexfile.toLatin1().data(), "rb+", HeadBuf, sizeof(FileHead) );
    ull key=hashkey(keyvalues.toStdString());//根据关键字利用索引值查找
    qDebug()<<key;
    SearchBTree(HeadBuf->head,key,&res);
    qDebug()<<res.pt;
    FREE_NODE(HeadBuf);

}
//删除索引
void Indexmanager::deleteIndex(QString index_name) {

    datafile=dirPath+index_name+".ix";
    indexfile=dirPath+index_name+".tid";

    //是否传入了空的路径或路径是否存在
    if (datafile.isEmpty() || !QFile::exists(datafile))
    {
        QMessageBox::critical(0,"错误","索引文件不存在",
                              QMessageBox::Ok|QMessageBox::Default,
                              QMessageBox::Cancel|QMessageBox::Escape,0);
        qDebug()<<"索引文件不存在";
        return;
    }
    QFileInfo FileInfo(datafile);;
    QFileInfo FileIn(indexfile);
    if(FileInfo.isFile()){
        QFile::remove(datafile);
        QFile::remove(indexfile);
    }
    QMessageBox::information(0,"提示","索引删除成功",
                             QMessageBox::Ok|QMessageBox::Default,
                             QMessageBox::Cancel|QMessageBox::Escape,0);
}

QString Indexmanager::checkindex(QString finame1, QString finame2) {
   QFile ic(indexrecordfile);
    if(!ic.open(QIODevice::ReadOnly|QIODevice::Text)){
         qDebug()<<"打开索引记录文件失败";
         return NULL;
    }
    QTextStream check(&ic);
    QString fieldrecord=check.readLine();//读取表头
    while(!fieldrecord.isNull()){
        QStringList listtemp=fieldrecord.split(",");
        if(listtemp[0]==finame1&&listtemp[1]==finame2){
            return listtemp[2];
        }
        fieldrecord=check.readLine();
    }//读取索引记录文件
    ic.close();
    return NULL;

}
