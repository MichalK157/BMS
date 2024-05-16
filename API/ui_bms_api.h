/********************************************************************************
** Form generated from reading UI file 'bms_apiUhsRiK.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef BMS_APIUHSRIK_H
#define BMS_APIUHSRIK_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_BMS
{
public:
    QWidget *centralwidget;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QPushButton *Confirm;
    QWidget *horizontalLayoutWidget;
    QHBoxLayout *horizontalLayout;
    QLabel *c1;
    QLabel *c2;
    QLabel *c3;
    QLabel *c4;
    QLabel *c5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *BMS)
    {
        if (BMS->objectName().isEmpty())
            BMS->setObjectName(QString::fromUtf8("BMS"));
        BMS->resize(640, 480);
        centralwidget = new QWidget(BMS);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayoutWidget = new QWidget(centralwidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(10, 320, 201, 101));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        Confirm = new QPushButton(verticalLayoutWidget);
        Confirm->setObjectName(QString::fromUtf8("Confirm"));

        verticalLayout->addWidget(Confirm);

        horizontalLayoutWidget = new QWidget(centralwidget);
        horizontalLayoutWidget->setObjectName(QString::fromUtf8("horizontalLayoutWidget"));
        horizontalLayoutWidget->setGeometry(QRect(10, 10, 611, 80));
        horizontalLayout = new QHBoxLayout(horizontalLayoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        c1 = new QLabel(horizontalLayoutWidget);
        c1->setObjectName(QString::fromUtf8("c1"));

        horizontalLayout->addWidget(c1);

        c2 = new QLabel(horizontalLayoutWidget);
        c2->setObjectName(QString::fromUtf8("c2"));

        horizontalLayout->addWidget(c2);

        c3 = new QLabel(horizontalLayoutWidget);
        c3->setObjectName(QString::fromUtf8("c3"));

        horizontalLayout->addWidget(c3);

        c4 = new QLabel(horizontalLayoutWidget);
        c4->setObjectName(QString::fromUtf8("c4"));

        horizontalLayout->addWidget(c4);

        c5 = new QLabel(horizontalLayoutWidget);
        c5->setObjectName(QString::fromUtf8("c5"));

        horizontalLayout->addWidget(c5);

        BMS->setCentralWidget(centralwidget);
        menubar = new QMenuBar(BMS);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 640, 22));
        BMS->setMenuBar(menubar);
        statusbar = new QStatusBar(BMS);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        BMS->setStatusBar(statusbar);

        retranslateUi(BMS);

        QMetaObject::connectSlotsByName(BMS);
    } // setupUi

    void retranslateUi(QMainWindow *BMS)
    {
        BMS->setWindowTitle(QCoreApplication::translate("BMS", "BMS", nullptr));
        Confirm->setText(QCoreApplication::translate("BMS", "confirm_button", nullptr));
        c1->setText(QCoreApplication::translate("BMS", "0.00V", nullptr));
        c2->setText(QCoreApplication::translate("BMS", "0.00V", nullptr));
        c3->setText(QCoreApplication::translate("BMS", "0.00V", nullptr));
        c4->setText(QCoreApplication::translate("BMS", "0.00V", nullptr));
        c5->setText(QCoreApplication::translate("BMS", "0.00V", nullptr));
    } // retranslateUi

};

namespace Ui {
    class BMS: public Ui_BMS {};
} // namespace Ui

QT_END_NAMESPACE

#endif // BMS_APIUHSRIK_H
