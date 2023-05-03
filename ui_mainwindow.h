/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Mainwindow
{
public:
    QWidget *centralwidget;
    QLineEdit *sqllineEdit;
    QTableWidget *tableWidget;
    QPushButton *tablemanage;
    QPushButton *datamanage;
    QPushButton *fieldmanage;
    QPushButton *rollback;
    QPushButton *commit;
    QPushButton *run;
    QLabel *label;
    QTreeView *treeView;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *create;
    QPushButton *del;

    void setupUi(QWidget *Mainwindow)
    {
        if (Mainwindow->objectName().isEmpty())
            Mainwindow->setObjectName(QString::fromUtf8("Mainwindow"));
        Mainwindow->resize(816, 587);
        Mainwindow->setStyleSheet(QString::fromUtf8("font: 10pt \"\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223\";"));
        centralwidget = new QWidget(Mainwindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setGeometry(QRect(0, 0, 811, 571));
        sqllineEdit = new QLineEdit(centralwidget);
        sqllineEdit->setObjectName(QString::fromUtf8("sqllineEdit"));
        sqllineEdit->setGeometry(QRect(210, 60, 481, 51));
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(210, 180, 481, 211));
        tablemanage = new QPushButton(centralwidget);
        tablemanage->setObjectName(QString::fromUtf8("tablemanage"));
        tablemanage->setGeometry(QRect(210, 400, 111, 51));
        datamanage = new QPushButton(centralwidget);
        datamanage->setObjectName(QString::fromUtf8("datamanage"));
        datamanage->setGeometry(QRect(390, 400, 111, 51));
        fieldmanage = new QPushButton(centralwidget);
        fieldmanage->setObjectName(QString::fromUtf8("fieldmanage"));
        fieldmanage->setGeometry(QRect(580, 400, 111, 51));
        rollback = new QPushButton(centralwidget);
        rollback->setObjectName(QString::fromUtf8("rollback"));
        rollback->setGeometry(QRect(410, 120, 111, 51));
        commit = new QPushButton(centralwidget);
        commit->setObjectName(QString::fromUtf8("commit"));
        commit->setGeometry(QRect(210, 120, 111, 51));
        run = new QPushButton(centralwidget);
        run->setObjectName(QString::fromUtf8("run"));
        run->setGeometry(QRect(580, 120, 111, 51));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 0, 111, 71));
        label->setStyleSheet(QString::fromUtf8("font: 24pt \"\345\215\216\346\226\207\351\232\266\344\271\246\";"));
        treeView = new QTreeView(centralwidget);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(0, 120, 201, 371));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(700, 70, 81, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(700, 190, 91, 31));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(40, 60, 111, 51));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(390, 460, 111, 41));
        pushButton_4 = new QPushButton(centralwidget);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(580, 460, 111, 41));
        pushButton_5 = new QPushButton(centralwidget);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(210, 460, 111, 41));
        create = new QPushButton(centralwidget);
        create->setObjectName(QString::fromUtf8("create"));
        create->setGeometry(QRect(700, 270, 93, 28));
        del = new QPushButton(centralwidget);
        del->setObjectName(QString::fromUtf8("del"));
        del->setGeometry(QRect(700, 320, 93, 28));

        retranslateUi(Mainwindow);

        QMetaObject::connectSlotsByName(Mainwindow);
    } // setupUi

    void retranslateUi(QWidget *Mainwindow)
    {
        Mainwindow->setWindowTitle(QCoreApplication::translate("Mainwindow", "Mainwindow", nullptr));
        sqllineEdit->setText(QCoreApplication::translate("Mainwindow", "\350\257\267\350\276\223\345\205\245SQL\345\221\275\344\273\244", nullptr));
        tablemanage->setText(QCoreApplication::translate("Mainwindow", "\350\241\250\347\256\241\347\220\206", nullptr));
        datamanage->setText(QCoreApplication::translate("Mainwindow", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        fieldmanage->setText(QCoreApplication::translate("Mainwindow", "\345\255\227\346\256\265\347\256\241\347\220\206", nullptr));
        rollback->setText(QCoreApplication::translate("Mainwindow", "\345\233\236\346\273\232", nullptr));
        commit->setText(QCoreApplication::translate("Mainwindow", "\346\217\220\344\272\244", nullptr));
        run->setText(QCoreApplication::translate("Mainwindow", "\350\277\220\350\241\214", nullptr));
        label->setText(QCoreApplication::translate("Mainwindow", "DBMS", nullptr));
        label_2->setText(QCoreApplication::translate("Mainwindow", "SQL\345\221\275\344\273\244", nullptr));
        label_3->setText(QCoreApplication::translate("Mainwindow", "\347\273\223\346\236\234\346\230\276\347\244\272", nullptr));
        pushButton->setText(QCoreApplication::translate("Mainwindow", "\346\227\245\345\277\227", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Mainwindow", "\351\207\215\346\226\260\347\231\273\351\231\206", nullptr));
        pushButton_4->setText(QCoreApplication::translate("Mainwindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        pushButton_5->setText(QCoreApplication::translate("Mainwindow", "\346\235\203\351\231\220\347\256\241\347\220\206", nullptr));
        create->setText(QCoreApplication::translate("Mainwindow", "\345\210\233\345\273\272\346\225\260\346\215\256\345\272\223", nullptr));
        del->setText(QCoreApplication::translate("Mainwindow", "\345\210\240\351\231\244\346\225\260\346\215\256\345\272\223", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Mainwindow: public Ui_Mainwindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
