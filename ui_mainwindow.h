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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QTreeView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QLabel *label;
    QGroupBox *groupBox_5;
    QGridLayout *gridLayout_5;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout;
    QPushButton *rollback;
    QPushButton *commit;
    QPushButton *exit;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_2;
    QPushButton *selectAction;
    QPushButton *newAction;
    QPushButton *deleteAction;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_3;
    QPushButton *tablemanage;
    QPushButton *datamanage;
    QPushButton *fieldmanage;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_4;
    QPushButton *privilege;
    QPushButton *psw;
    QPushButton *rland;
    QGroupBox *groupBox_6;
    QWidget *layoutWidget;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QGroupBox *groupBox_7;
    QTableWidget *tableWidget;
    QLineEdit *sqllineEdit;
    QGroupBox *groupBox_8;
    QPushButton *run;
    QTreeView *treeView;
    QPushButton *log;
    QGroupBox *groupBox_9;
    QTextEdit *text;
    QLineEdit *time;
    QLabel *label_2;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->setEnabled(true);
        MainWindow->resize(1109, 677);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setStyleSheet(QString::fromUtf8("font: 10pt \"\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223\";"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setGeometry(QRect(0, 0, 1111, 691));
        centralwidget->setStyleSheet(QString::fromUtf8("font: 10pt \"\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223\";\n"
"background-image: url(:/picture/77.jpg);\n"
""));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 0, 111, 71));
        label->setStyleSheet(QString::fromUtf8("font: 24pt \"\345\215\216\346\226\207\351\232\266\344\271\246\";"));
        groupBox_5 = new QGroupBox(centralwidget);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        groupBox_5->setGeometry(QRect(240, 430, 561, 221));
        groupBox_5->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 240, 255);\n"
"background-image: url(:/picture/88.jpg);\n"
"\n"
"\n"
""));
        gridLayout_5 = new QGridLayout(groupBox_5);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        groupBox = new QGroupBox(groupBox_5);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(229, 254, 255);\n"
""));
        verticalLayout = new QVBoxLayout(groupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        rollback = new QPushButton(groupBox);
        rollback->setObjectName(QString::fromUtf8("rollback"));
        rollback->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(rollback);

        commit = new QPushButton(groupBox);
        commit->setObjectName(QString::fromUtf8("commit"));
        commit->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(commit);

        exit = new QPushButton(groupBox);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setStyleSheet(QString::fromUtf8(""));

        verticalLayout->addWidget(exit);


        gridLayout_5->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(groupBox_5);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setStyleSheet(QString::fromUtf8("background-color: rgb(228, 255, 242);\n"
"background-image: url(:/picture/88.jpg);"));
        gridLayout_2 = new QGridLayout(groupBox_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        selectAction = new QPushButton(groupBox_2);
        selectAction->setObjectName(QString::fromUtf8("selectAction"));

        gridLayout_2->addWidget(selectAction, 0, 0, 1, 1);

        newAction = new QPushButton(groupBox_2);
        newAction->setObjectName(QString::fromUtf8("newAction"));

        gridLayout_2->addWidget(newAction, 1, 0, 1, 1);

        deleteAction = new QPushButton(groupBox_2);
        deleteAction->setObjectName(QString::fromUtf8("deleteAction"));

        gridLayout_2->addWidget(deleteAction, 2, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_2, 0, 1, 1, 1);

        groupBox_3 = new QGroupBox(groupBox_5);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 252, 240);\n"
""));
        gridLayout_3 = new QGridLayout(groupBox_3);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        tablemanage = new QPushButton(groupBox_3);
        tablemanage->setObjectName(QString::fromUtf8("tablemanage"));

        gridLayout_3->addWidget(tablemanage, 0, 0, 1, 1);

        datamanage = new QPushButton(groupBox_3);
        datamanage->setObjectName(QString::fromUtf8("datamanage"));

        gridLayout_3->addWidget(datamanage, 1, 0, 1, 1);

        fieldmanage = new QPushButton(groupBox_3);
        fieldmanage->setObjectName(QString::fromUtf8("fieldmanage"));

        gridLayout_3->addWidget(fieldmanage, 2, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_3, 0, 2, 1, 1);

        groupBox_4 = new QGroupBox(groupBox_5);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 244, 238);\n"
"background-image: url(:/picture/88.jpg);"));
        gridLayout_4 = new QGridLayout(groupBox_4);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        privilege = new QPushButton(groupBox_4);
        privilege->setObjectName(QString::fromUtf8("privilege"));

        gridLayout_4->addWidget(privilege, 2, 0, 1, 1);

        psw = new QPushButton(groupBox_4);
        psw->setObjectName(QString::fromUtf8("psw"));

        gridLayout_4->addWidget(psw, 1, 0, 1, 1);

        rland = new QPushButton(groupBox_4);
        rland->setObjectName(QString::fromUtf8("rland"));

        gridLayout_4->addWidget(rland, 0, 0, 1, 1);


        gridLayout_5->addWidget(groupBox_4, 0, 3, 1, 1);

        groupBox_6 = new QGroupBox(centralwidget);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        groupBox_6->setGeometry(QRect(240, 50, 561, 381));
        groupBox_6->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 240, 255);\n"
"background-image: url(:/picture/88.jpg);"));
        layoutWidget = new QWidget(groupBox_6);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(520, 30, 31, 331));
        gridLayout = new QGridLayout(layoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223\";"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        label_5 = new QLabel(layoutWidget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223\";"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        label_6 = new QLabel(layoutWidget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223\";"));

        gridLayout->addWidget(label_6, 2, 0, 1, 1);

        label_7 = new QLabel(layoutWidget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setStyleSheet(QString::fromUtf8("font: 14pt \"\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223\";"));

        gridLayout->addWidget(label_7, 3, 0, 1, 1);

        groupBox_7 = new QGroupBox(groupBox_6);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setGeometry(QRect(0, 0, 521, 381));
        tableWidget = new QTableWidget(groupBox_7);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(10, 70, 501, 301));
        tableWidget->setMouseTracking(true);
        tableWidget->setTabletTracking(true);
        tableWidget->setStyleSheet(QString::fromUtf8(""));
        sqllineEdit = new QLineEdit(groupBox_7);
        sqllineEdit->setObjectName(QString::fromUtf8("sqllineEdit"));
        sqllineEdit->setGeometry(QRect(10, 10, 491, 51));
        sqllineEdit->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"  \n"
"	background-image: url(:/picture/b5.jpg);\n"
" border-color: rgb(93, 171, 255);\n"
"    border-radius: 10px;\n"
"    border-style: outset;\n"
"  \n"
"    }"));
        groupBox_8 = new QGroupBox(centralwidget);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        groupBox_8->setGeometry(QRect(10, 50, 221, 601));
        groupBox_8->setStyleSheet(QString::fromUtf8("background-image: url(:/picture/88.jpg);"));
        run = new QPushButton(groupBox_8);
        run->setObjectName(QString::fromUtf8("run"));
        run->setGeometry(QRect(10, 10, 201, 51));
        run->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  \n"
" border-color: rgb(93, 171, 255);\n"
"    border-radius: 20px;\n"
"    border-style: outset;\n"
" \n"
" background-image: url(:/picture/b3.jpg);\n"
"    }"));
        treeView = new QTreeView(groupBox_8);
        treeView->setObjectName(QString::fromUtf8("treeView"));
        treeView->setGeometry(QRect(10, 70, 201, 451));
        treeView->setStyleSheet(QString::fromUtf8("background-image: url(:/picture/88.jpg);"));
        log = new QPushButton(groupBox_8);
        log->setObjectName(QString::fromUtf8("log"));
        log->setGeometry(QRect(10, 530, 201, 51));
        log->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  \n"
" border-color: rgb(93, 171, 255);\n"
"    border-radius: 20px;\n"
"    border-style: outset;\n"
" \n"
" background-image: url(:/picture/b3.jpg);\n"
"    }"));
        groupBox_9 = new QGroupBox(centralwidget);
        groupBox_9->setObjectName(QString::fromUtf8("groupBox_9"));
        groupBox_9->setGeometry(QRect(810, 50, 291, 591));
        groupBox_9->setStyleSheet(QString::fromUtf8("background-color: rgb(235, 240, 255);\n"
"background-image: url(:/picture/88.jpg);"));
        text = new QTextEdit(groupBox_9);
        text->setObjectName(QString::fromUtf8("text"));
        text->setGeometry(QRect(10, 10, 271, 521));
        text->setStyleSheet(QString::fromUtf8("font: 10pt \"\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223\";\n"
"font: 10pt \"\345\215\216\346\226\207\344\270\255\345\256\213\";\n"
"background-image: url(:/picture/99.jpg);"));
        time = new QLineEdit(groupBox_9);
        time->setObjectName(QString::fromUtf8("time"));
        time->setGeometry(QRect(100, 540, 181, 41));
        time->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"  \n"
"	background-image: url(:/picture/b5.jpg);\n"
" border-color: rgb(93, 171, 255);\n"
"    border-radius: 10px;\n"
"    border-style: outset;\n"
"  \n"
"    }"));
        label_2 = new QLabel(groupBox_9);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(11, 540, 81, 41));
        label_2->setStyleSheet(QString::fromUtf8("QLabel {\n"
"  \n"
"	background-image: url(:/picture/b5.jpg);\n"
" border-color: rgb(93, 171, 255);\n"
"    border-radius: 10px;\n"
"    border-style: outset;\n"
"  \n"
"    }"));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mainwindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "DBMS", nullptr));
        groupBox_5->setTitle(QString());
        groupBox->setTitle(QString());
        rollback->setText(QCoreApplication::translate("MainWindow", "\345\233\236\346\273\232", nullptr));
        commit->setText(QCoreApplication::translate("MainWindow", "\346\217\220\344\272\244", nullptr));
        exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
        groupBox_2->setTitle(QString());
        selectAction->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\225\260\346\215\256\345\272\223", nullptr));
        newAction->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\346\225\260\346\215\256\345\272\223", nullptr));
        deleteAction->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\225\260\346\215\256\345\272\223", nullptr));
        groupBox_3->setTitle(QString());
        tablemanage->setText(QCoreApplication::translate("MainWindow", "\350\241\250\347\256\241\347\220\206", nullptr));
        datamanage->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        fieldmanage->setText(QCoreApplication::translate("MainWindow", "\345\255\227\346\256\265\347\256\241\347\220\206", nullptr));
        groupBox_4->setTitle(QString());
        privilege->setText(QCoreApplication::translate("MainWindow", "\346\235\203\351\231\220\347\256\241\347\220\206", nullptr));
        psw->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        rland->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\347\231\273\351\231\206", nullptr));
        groupBox_6->setTitle(QString());
        label_4->setText(QCoreApplication::translate("MainWindow", "\347\273\223", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\346\236\234", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\346\230\276", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "\347\244\272", nullptr));
        groupBox_7->setTitle(QString());
        sqllineEdit->setText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245SQL\345\221\275\344\273\244", nullptr));
        groupBox_8->setTitle(QString());
        run->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        log->setText(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        groupBox_9->setTitle(QString());
        text->setHtml(QCoreApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'\345\215\216\346\226\207\344\270\255\345\256\213'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223'; font-size:12pt; color:#000000;\">1.\346\225\260\346\215\256\345\272\223\347\233\270\345\205\263</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \345\210\233\345\273\272\346\225\260\346\215\256\345\272\223\357\274\232create data"
                        "base DBname;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \345\210\240\351\231\244\346\225\260\346\215\256\345\272\223\357\274\232drop database DBname;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">2.\350\241\250\347\256\241\347\220\206</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \345\210\233\345\273\272\350\241\250\357\274\232create table tablename;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-inde"
                        "nt:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \345\210\240\351\231\244\350\241\250\357\274\232drop table tablename;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">3.\345\255\227\346\256\265\347\256\241\347\220\206</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \345\242\236\345\212\240\345\255\227\346\256\265\357\274\232alter table tablename add colname number;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#0"
                        "00000;\">* \345\210\240\351\231\244\345\255\227\346\256\265\357\274\232alter table tablename drop column colname;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \344\277\256\346\224\271\345\255\227\346\256\265\357\274\232alter table tablename modify colname not null;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">4.\346\225\260\346\215\256\347\256\241\347\220\206</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \346\217\222\345\205\245\357\274\232insert into tablename v"
                        "alues(**,**,*);</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \345\210\240\351\231\244\357\274\232delete from users where userid=001;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \346\233\264\346\226\260\357\274\232update tablename set username=111 where id=2;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">5.\346\237\245\350\257\242</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px"
                        ";\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \346\237\245\350\257\242\345\205\250\351\203\250\357\274\232select * from tablename;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \346\237\245\350\257\242\346\214\207\345\256\232\345\255\227\346\256\265\346\211\200\346\234\211\350\256\260\345\275\225\357\274\232select (fieldname1,fieldname2) from tablename;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* ****\346\263\250\346\204\217\357\274\232\346\217\220\345\217\226\346\213\254\345\217\267\351\207\214\347\232\204\346\211\200\346\234\211\345\206\205\345\256\271\357\274\214\347\204\266\345\220\216\345"
                        "\261\225\347\244\272\347\232\204\346\227\266\345\200\231\345\206\215\347\224\250\346\255\243\345\210\231\350\277\233\344\270\200\346\255\245\350\247\243\346\236\220</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \346\237\245\350\257\242\346\214\207\345\256\232\345\255\227\346\256\265\345\222\214where\346\235\241\344\273\266\357\274\210\345\215\225\344\270\200\346\235\241\344\273\266\357\274\211:select (sname,sno,sex) from tablename where id=1009;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">6.\347\264\242\345\274\225</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0"
                        "px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* create index idxname on tablename(fieldname);</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* drop index idxname on tablename;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">7.\345\257\274\345\205\245sql\350\204\232\346\234\254</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* import script E:/database.sql;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; mar"
                        "gin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">8.\345\257\271\350\261\241\346\235\203\351\231\220\350\265\213\344\272\210\345\222\214\345\233\236\346\224\266</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* \357\274\210\344\273\273\346\204\217\346\225\260\351\207\217\347\232\204\346\235\203\351\231\220\345\222\214\347\224\250\346\210\267\345\220\215\357\274\211</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* grant create,drop,update,insert,delete on tablename to username1,username2;</span></p>\n"
"<p style=\" margin-top:12px; margin-bot"
                        "tom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">* revoke create,drop,update,insert,delete on tablename from username;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">9.\347\263\273\347\273\237\346\235\203\351\231\220\350\265\213\344\272\210\345\222\214\345\233\236\346\224\266</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">*grant create,drop,update,insert,delete to username;</span></p>\n"
"<p style=\" margin-top:12px; margin-bottom:12px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" fo"
                        "nt-family:'Courier New'; font-size:12pt; font-weight:600; color:#000000;\">*revoke create,drop,update,insert,delete from username;</span></p></body></html>", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\346\220\234\347\264\242\347\224\250\346\227\266\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
