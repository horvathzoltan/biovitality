/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_AddSoldItem;
    QLabel *label;
    QPushButton *pushButton_addressImport;
    QPushButton *pushButton_tetelImport;
    QPushButton *pushButton_dbtest;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QPlainTextEdit *plainTextEdit_status;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(986, 568);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName("verticalLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_AddSoldItem = new QPushButton(centralwidget);
        pushButton_AddSoldItem->setObjectName("pushButton_AddSoldItem");

        horizontalLayout->addWidget(pushButton_AddSoldItem);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        pushButton_addressImport = new QPushButton(centralwidget);
        pushButton_addressImport->setObjectName("pushButton_addressImport");

        horizontalLayout->addWidget(pushButton_addressImport);

        pushButton_tetelImport = new QPushButton(centralwidget);
        pushButton_tetelImport->setObjectName("pushButton_tetelImport");

        horizontalLayout->addWidget(pushButton_tetelImport);

        pushButton_dbtest = new QPushButton(centralwidget);
        pushButton_dbtest->setObjectName("pushButton_dbtest");

        horizontalLayout->addWidget(pushButton_dbtest);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        plainTextEdit_status = new QPlainTextEdit(centralwidget);
        plainTextEdit_status->setObjectName("plainTextEdit_status");
        plainTextEdit_status->setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction);

        verticalLayout->addWidget(plainTextEdit_status);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_AddSoldItem->setText(QCoreApplication::translate("MainWindow", "AddSoldItem", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_addressImport->setText(QCoreApplication::translate("MainWindow", "C\303\255m Import", nullptr));
        pushButton_tetelImport->setText(QCoreApplication::translate("MainWindow", "T\303\251tel Import", nullptr));
        pushButton_dbtest->setText(QCoreApplication::translate("MainWindow", "DBtest", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
