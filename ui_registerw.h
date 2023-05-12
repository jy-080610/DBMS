/********************************************************************************
** Form generated from reading UI file 'registerw.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERW_H
#define UI_REGISTERW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_registerw
{
public:
    QLabel *label;
    QComboBox *dbName;
    QLineEdit *username;
    QLineEdit *psw1;
    QLineEdit *psw2;
    QLabel *label_2;
    QPushButton *registerButton;
    QPushButton *quitButton;

    void setupUi(QWidget *registerw)
    {
        if (registerw->objectName().isEmpty())
            registerw->setObjectName(QString::fromUtf8("registerw"));
        registerw->resize(501, 431);
        registerw->setStyleSheet(QString::fromUtf8("font: 10pt \"\346\226\271\346\255\243\347\262\227\351\273\221\345\256\213\347\256\200\344\275\223\";"));
        label = new QLabel(registerw);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(0, 0, 501, 431));
        label->setStyleSheet(QString::fromUtf8("background-image: url(:/picture/p3.jpg);"));
        dbName = new QComboBox(registerw);
        dbName->setObjectName(QString::fromUtf8("dbName"));
        dbName->setGeometry(QRect(240, 60, 251, 41));
        dbName->setStyleSheet(QString::fromUtf8("QComboBox {\n"
"  \n"
" background-image: url(:/picture/b5.jpg);\n"
" border-color: rgb(93, 171, 255);\n"
"    border-radius: 10px;\n"
"    border-style: outset;\n"
"  \n"
"    }"));
        username = new QLineEdit(registerw);
        username->setObjectName(QString::fromUtf8("username"));
        username->setGeometry(QRect(240, 120, 251, 41));
        username->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"  \n"
" background-image: url(:/picture/b5.jpg);\n"
" border-color: rgb(93, 171, 255);\n"
"    border-radius: 10px;\n"
"    border-style: outset;\n"
"  \n"
"    }"));
        psw1 = new QLineEdit(registerw);
        psw1->setObjectName(QString::fromUtf8("psw1"));
        psw1->setGeometry(QRect(240, 190, 251, 41));
        psw1->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"  \n"
" background-image: url(:/picture/b5.jpg);\n"
" border-color: rgb(93, 171, 255);\n"
"    border-radius: 10px;\n"
"    border-style: outset;\n"
"  \n"
"    }"));
        psw2 = new QLineEdit(registerw);
        psw2->setObjectName(QString::fromUtf8("psw2"));
        psw2->setGeometry(QRect(240, 250, 251, 41));
        psw2->setStyleSheet(QString::fromUtf8("QLineEdit {\n"
"  \n"
" background-image: url(:/picture/b5.jpg);\n"
" border-color: rgb(93, 171, 255);\n"
"    border-radius: 10px;\n"
"    border-style: outset;\n"
"  \n"
"    }"));
        label_2 = new QLabel(registerw);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 60, 201, 191));
        label_2->setStyleSheet(QString::fromUtf8("font: 40pt \"\345\215\216\346\226\207\351\232\266\344\271\246\";"));
        registerButton = new QPushButton(registerw);
        registerButton->setObjectName(QString::fromUtf8("registerButton"));
        registerButton->setGeometry(QRect(30, 320, 171, 51));
        registerButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  \n"
"	border-color: rgb(93, 171, 255);\n"
"    border-radius: 20px;\n"
"    border-style: outset;\n"
"   background-image: url(:/picture/p2.jpg);\n"
"    }"));
        quitButton = new QPushButton(registerw);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));
        quitButton->setGeometry(QRect(310, 320, 171, 51));
        quitButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"  \n"
"	border-color: rgb(93, 171, 255);\n"
"    border-radius: 20px;\n"
"    border-style: outset;\n"
"   background-image: url(:/picture/p2.jpg);\n"
"    }"));

        retranslateUi(registerw);

        QMetaObject::connectSlotsByName(registerw);
    } // setupUi

    void retranslateUi(QWidget *registerw)
    {
        registerw->setWindowTitle(QCoreApplication::translate("registerw", "registerw", nullptr));
        label->setText(QString());
        username->setText(QCoreApplication::translate("registerw", "\347\224\250\346\210\267\345\220\215", nullptr));
        psw1->setText(QCoreApplication::translate("registerw", "\345\257\206\347\240\201", nullptr));
        psw2->setText(QCoreApplication::translate("registerw", "\347\241\256\350\256\244\345\257\206\347\240\201", nullptr));
        label_2->setText(QCoreApplication::translate("registerw", "DBMS", nullptr));
        registerButton->setText(QCoreApplication::translate("registerw", "\346\263\250\345\206\214", nullptr));
        quitButton->setText(QCoreApplication::translate("registerw", "\351\200\200\345\207\272", nullptr));
    } // retranslateUi

};

namespace Ui {
    class registerw: public Ui_registerw {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERW_H
