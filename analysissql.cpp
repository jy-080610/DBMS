//
// Created by lx on 2023/4/5.
//
//正则表达式匹配
#include "analysissql.h"
#include "qdebug.h"

//分析SQL语句:正则表达式

AnalysisSQL::AnalysisSQL() {//初始化构造器
    //保存所有可能用到的正则表达式
    //1.数据库
    //创建数据库：create database 数据库名称;
    //删除数据库：drop database 数据库名称;
    //sqlList.insert(0,"(?:create|CREATE)(?:\\s*)(?:database|DATABASE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");
    //sqlList.push_back("(?:drop|DROP)(?:\\s*)(?:database|DATABASE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");

    //2.表：
    //sqlList.push_back("(?:create|CREATE)(?:\\s*)(?:table|TABLE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");
    //sqlList.push_back("(?:drop|DROP)(?:\\s*)(?:table|TABLE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");

    //3.对表的数据操作：
    //()表示分组，\\b表示单词边界，\\w表示单词字符，+表示一个或多个
    //\\w+表示一个或多个单词字符
    //\\s*表示0个或多个空白字符
    //sqlList.push_back("((?:insert into)|(?:INSERT INTO))(\\w+)(?:values)(?:\\s*)\\((.+)\\(?:\\s*);");
    //sqlList.push_back("(?:delete|DELETE)\\s*(?:from|FROM)\\s*(\\w+)\\s*(?:where|WHERE)\\s*(\\w+)\\s*(<|>|=)\\s*(\\w+)(?:\\s*);");
    //sqlList.push_back("(?:update|UPDATE)(?:\\s*)(\\w+)(?:\\s*)(?:set|SET)(?:\\s*)(\\w+)(?:\\s*)=(\\w+)(?:\\s*)(?:where|WHERE)(?:\\s*)(\\w+)(?:\\s*)(<|=|>)(?:\\s*)(\\w+)(?:\\s*);");

    //4.字段操作：
    //sqlList.push_back("(?:alter|ALTER)\\s*(?:table|TABLE)\\s*(\\w+)\\s*(?:add|ADD)\\s*(\\w+)\\s*(number|char|varchar|date|NUMBER|CHAR|VARCHAR|DATE)\\s*(primary key|PRIMARY KEY)?\\s*(not null|NOT NULL)?;");
    //sqlList.push_back("(?:alter|ALTER)\\s*(?:table|TABLE)\\s*(\\w+)\\s*(?:drop|DROP)\\s*(?:column|COLUMN)\\s*(\\w+)(?:\\s*);");
    //sqlList.push_back("(?:alter|ALTER)\\s*(?:table|TABLE)\\s*(\\w+)\\s*(?:modify|MODIFY)\\s*(\\w+)\\s*(primary key|PRIMARY KEY)?\\s*(not null|NOT NULL)?;");

    //5.查询操作：
    //[\\*]表示*，\\w表示单词字符，+表示一个或多个
    //((.+)\\)表示括号中的任意字符
    //(?:\\s*)表示0个或多个空白字符
//    sqlList.push_back("(?:select|SELECT)(?:\\s*)([\\*])(?:\\s*)(?:from|FROM)(?:\\s*)(\\w+)(?:\\s*);");
//    sqlList.push_back("(?:select|SELECT)(?:\\s*)\\((.+)\\)(?:\\s*)(?:FROM|from)(?:\\s*)(\\w+)(?:\\s*);");
//    sqlList.push_back("(?:select|SELECT)(?:\\s+)\\((.+)\\)(?:\\s*)(?:FROM|from)(?:\\s*)(\\w+)(?:\\s*)where(?:\\s*)(\\w+)(?:\\s*)(<|=|>)(\\w+)(?:\\s*);");

    //6.索引：
    //sqlList.push_back("(?:create|CREATE)(?:\\s*)(?:index|INDEX)(?:\\s*)(\\w+)(?:\\s*)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*)\\((.+)\\);");
    //sqlList.push_back("(?:drop|DROP)(?:\\s*)(?:index|INDEX)(?:\\s*)(\\w+)(?:\\s*)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*);");

    //7.权限：
    //（?:\\s)与(?:\\s*)的不同：\\s表示空白字符，\\s*表示0个或多个空白字符
    //(?:\s+)表示1个或多个空白字符
    //(.+)表示任意字符
    //sqlList.push_back("(?:grant|Grant)(?:\\s)+(.+)(?:\\s+)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*)(?:to|TO)(?:\\s)+(.+)(?:\\s*);");
    //sqlList.push_back("(?:revoke|REVOKE)(?:\\s)+(.+)(?:\\s+)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*)(?:from|FROM)(?:\\s)+(.+)(?:\\s*);");
}
    /*
     * 通过正则表达式匹配sql语句
     * @param sql sql语句
     * @return 含有关键字的sql语句
     */

    QStringList AnalysisSQL::resolveSql(QString sql) {
        qDebug() << "sql语句为:" << sql;
        //通过分析SQL语句得到有用的SQL的列表
        QStringList keyWordList;
        QStringList sqlList;
        sqlList.push_back("(?:create|CREATE)(?:\\s*)(?:database|DATABASE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");
        sqlList.push_back("(?:drop|DROP)(?:\\s*)(?:database|DATABASE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");
        sqlList.push_back("(?:create|CREATE)(?:\\s*)(?:table|TABLE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");
        sqlList.push_back("(?:drop|DROP)(?:\\s*)(?:table|TABLE)(?:\\s*)(\\b\\w+\\b)(?:\\s*);");
        sqlList.push_back("(?:alter|ALTER)\\s*(?:table|TABLE)\\s*(\\w+)\\s*(?:add|ADD)\\s*(\\w+)\\s*(number|char|varchar|date|NUMBER|CHAR|VARCHAR|DATE)\\s*(primary key|PRIMARY KEY)?\\s*(not null|NOT NULL)?;");
        sqlList.push_back("(?:alter|ALTER)\\s*(?:table|TABLE)\\s*(\\w+)\\s*(?:drop|DROP)\\s*(?:column|COLUMN)\\s*(\\w+)(?:\\s*);");
        sqlList.push_back("(?:alter|ALTER)\\s*(?:table|TABLE)\\s*(\\w+)\\s*(?:modify|MODIFY)\\s*(\\w+)\\s*(primary key|PRIMARY KEY)?\\s*(not null|NOT NULL)?;");
        sqlList.push_back("((?:insert into)|(?:INSERT INTO))(\\w+)(?:values)(?:\\s*)\\((.+)\\(?:\\s*);");
        sqlList.push_back("(?:delete|DELETE)\\s*(?:from|FROM)\\s*(\\w+)\\s*(?:where|WHERE)\\s*(\\w+)\\s*(<|>|=)\\s*(\\w+)(?:\\s*);");
        sqlList.push_back("(?:update|UPDATE)(?:\\s*)(\\w+)(?:\\s*)(?:set|SET)(?:\\s*)(\\w+)(?:\\s*)=(\\w+)(?:\\s*)(?:where|WHERE)(?:\\s*)(\\w+)(?:\\s*)(<|=|>)(?:\\s*)(\\w+)(?:\\s*);");
        sqlList.push_back("(?:select|SELECT)(?:\\s*)([\\*])(?:\\s*)(?:from|FROM)(?:\\s*)(\\w+)(?:\\s*);");
        sqlList.push_back("(?:select|SELECT)(?:\\s*)\\((.+)\\)(?:\\s*)(?:FROM|from)(?:\\s*)(\\w+)(?:\\s*);");
        sqlList.push_back("(?:select|SELECT)(?:\\s+)\\((.+)\\)(?:\\s*)(?:FROM|from)(?:\\s*)(\\w+)(?:\\s*)where(?:\\s*)(\\w+)(?:\\s*)(<|=|>)(\\w+)(?:\\s*);");
        sqlList.push_back("(?:create|CREATE)(?:\\s*)(?:index|INDEX)(?:\\s*)(\\w+)(?:\\s*)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*)\\((.+)\\);");
        sqlList.push_back("(?:drop|DROP)(?:\\s*)(?:index|INDEX)(?:\\s*)(\\w+)(?:\\s*)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*);");
        sqlList.push_back("(?:grant|Grant)(?:\\s)+(.+)(?:\\s+)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*)(?:to|TO)(?:\\s)+(.+)(?:\\s*);");
        sqlList.push_back("(?:revoke|REVOKE)(?:\\s)+(.+)(?:\\s+)(?:on|ON)(?:\\s*)(\\w+)(?:\\s*)(?:from|FROM)(?:\\s)+(.+)(?:\\s*);");


        for(int i=0;i<sqlList.size();i++) {
            QRegExp rx(sqlList[i]);//正则表达式
            int pos = rx.indexIn(sql);//匹配
            if (pos != -1) {//匹配成功
                keyWordList = rx.capturedTexts();//返回所有匹配的字符串
                keyWordList[0] = QString::number(i);//将匹配的正则表达式的序号保存到第一个元素中
                qDebug() << "匹配成功:" << keyWordList;
                return keyWordList;
            }
        }
            qDebug() << "匹配失败";
            return keyWordList;
        }

