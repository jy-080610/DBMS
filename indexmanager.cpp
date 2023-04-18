//
// Created by Asus on 2023/4/17.
//

#include <QStringList>
#include "indexmanager.h"

Indexmanager::Indexmanager() {

}

Indexmanager::Indexmanager(QString tablename) {

}

void Indexmanager::createFalseIndex(QStringList keyword) {

}

int Indexmanager::Search(BTNode *NodeBuf, ull key) {
    return 0;
}

void Indexmanager::SearchBTree(unit node_pos, ull key, Result *r) {

}

void Indexmanager::upFileHead(unit new_head_pos) {

}

void Indexmanager::newRoot(unit head_pos, ull key, _data data, unit ap) {

}

unit Indexmanager::split(BTNode *NodeBuf, unit node_pos, sint s) {
    return 0;
}

BTNode Indexmanager::Insert(unit node_pos, sint i, ull key, uint ap, _data data) {
    return BTNode();
}

void Indexmanager::InsertBTree(unit head_pos, ull key, unit node_pos, sint i, _data data) {

}

void Indexmanager::insertData(char *con, ull key) {

}

ull Indexmanager::hashkey(string s) {
    return 0;
}

void Indexmanager::SelectBtree(QString index_name, QString keyvalues) {

}

void Indexmanager::deleteIndex(QString index_name) {

}

QString Indexmanager::checkindex(QString finame1, QString finame2) {
    return QString();
}
