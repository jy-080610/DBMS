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

class Ui_MainWindow
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
    QPushButton *log;
    QPushButton *rland;
    QPushButton *psw;
    QPushButton *privilege;
    QPushButton *newAction;
    QPushButton *deleteAction;
    QPushButton *selectAction;
    QPushButton *exit;

    void setupUi(QWidget *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(816, 587);
        MainWindow->setStyleSheet(QString::fromUtf8("font: 10pt \"\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223\";"));
        centralwidget = new QWidget(MainWindow);
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
        treeView->setGeometry(QRect(10, 120, 191, 371));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(700, 70, 81, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(700, 180, 91, 31));
        log = new QPushButton(centralwidget);
        log->setObjectName(QString::fromUtf8("log"));
        log->setGeometry(QRect(40, 60, 111, 51));
        rland = new QPushButton(centralwidget);
        rland->setObjectName(QString::fromUtf8("rland"));
        rland->setGeometry(QRect(390, 460, 111, 41));
        psw = new QPushButton(centralwidget);
        psw->setObjectName(QString::fromUtf8("psw"));
        psw->setGeometry(QRect(580, 460, 111, 41));
        privilege = new QPushButton(centralwidget);
        privilege->setObjectName(QString::fromUtf8("privilege"));
        privilege->setGeometry(QRect(210, 460, 111, 41));
        newAction = new QPushButton(centralwidget);
        newAction->setObjectName(QString::fromUtf8("newAction"));
        newAction->setGeometry(QRect(700, 220, 93, 51));
        deleteAction = new QPushButton(centralwidget);
        deleteAction->setObjectName(QString::fromUtf8("deleteAction"));
        deleteAction->setGeometry(QRect(700, 280, 93, 51));
        selectAction = new QPushButton(centralwidget);
        selectAction->setObjectName(QString::fromUtf8("selectAction"));
        selectAction->setGeometry(QRect(700, 340, 93, 51));
        exit = new QPushButton(centralwidget);
        exit->setObjectName(QString::fromUtf8("exit"));
        exit->setGeometry(QRect(700, 410, 93, 91));

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QWidget *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Mainwindow", nullptr));
        sqllineEdit->setText(QCoreApplication::translate("MainWindow", "\350\257\267\350\276\223\345\205\245SQL\345\221\275\344\273\244", nullptr));
        tablemanage->setText(QCoreApplication::translate("MainWindow", "\350\241\250\347\256\241\347\220\206", nullptr));
        datamanage->setText(QCoreApplication::translate("MainWindow", "\346\225\260\346\215\256\347\256\241\347\220\206", nullptr));
        fieldmanage->setText(QCoreApplication::translate("MainWindow", "\345\255\227\346\256\265\347\256\241\347\220\206", nullptr));
        rollback->setText(QCoreApplication::translate("MainWindow", "\345\233\236\346\273\232", nullptr));
        commit->setText(QCoreApplication::translate("MainWindow", "\346\217\220\344\272\244", nullptr));
        run->setText(QCoreApplication::translate("MainWindow", "\350\277\220\350\241\214", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "DBMS", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "SQL\345\221\275\344\273\244", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\273\223\346\236\234\346\230\276\347\244\272", nullptr));
        log->setText(QCoreApplication::translate("MainWindow", "\346\227\245\345\277\227", nullptr));
        rland->setText(QCoreApplication::translate("MainWindow", "\351\207\215\346\226\260\347\231\273\351\231\206", nullptr));
        psw->setText(QCoreApplication::translate("MainWindow", "\344\277\256\346\224\271\345\257\206\347\240\201", nullptr));
        privilege->setText(QCoreApplication::translate("MainWindow", "\346\235\203\351\231\220\347\256\241\347\220\206", nullptr));
        newAction->setText(QCoreApplication::translate("MainWindow", "\345\210\233\345\273\272\346\225\260\346\215\256\345\272\223", nullptr));
        deleteAction->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244\346\225\260\346\215\256\345\272\223", nullptr));
        selectAction->setText(QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\225\260\346\215\256\345\272\223", nullptr));
        exit->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
