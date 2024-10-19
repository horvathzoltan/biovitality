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
#include <QtWidgets/QGroupBox>
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
    QPushButton *pushButton_dbtest;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox_Import;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_PartnerImport;
    QPushButton *pushButton_AddressImport;
    QPushButton *pushButton_TetelImport;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPlainTextEdit *plainTextEdit_status;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton_ToClipBoard;
    QPushButton *pushButton_ToLogFile;

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

        pushButton_dbtest = new QPushButton(centralwidget);
        pushButton_dbtest->setObjectName("pushButton_dbtest");

        horizontalLayout->addWidget(pushButton_dbtest);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        groupBox_Import = new QGroupBox(centralwidget);
        groupBox_Import->setObjectName("groupBox_Import");
        horizontalLayout_4 = new QHBoxLayout(groupBox_Import);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        pushButton_PartnerImport = new QPushButton(groupBox_Import);
        pushButton_PartnerImport->setObjectName("pushButton_PartnerImport");

        horizontalLayout_4->addWidget(pushButton_PartnerImport);

        pushButton_AddressImport = new QPushButton(groupBox_Import);
        pushButton_AddressImport->setObjectName("pushButton_AddressImport");

        horizontalLayout_4->addWidget(pushButton_AddressImport);

        pushButton_TetelImport = new QPushButton(groupBox_Import);
        pushButton_TetelImport->setObjectName("pushButton_TetelImport");

        horizontalLayout_4->addWidget(pushButton_TetelImport);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);


        verticalLayout->addWidget(groupBox_Import);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        plainTextEdit_status = new QPlainTextEdit(centralwidget);
        plainTextEdit_status->setObjectName("plainTextEdit_status");
        plainTextEdit_status->setTextInteractionFlags(Qt::TextInteractionFlag::NoTextInteraction);

        horizontalLayout_2->addWidget(plainTextEdit_status);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        pushButton_ToClipBoard = new QPushButton(centralwidget);
        pushButton_ToClipBoard->setObjectName("pushButton_ToClipBoard");

        verticalLayout_2->addWidget(pushButton_ToClipBoard);

        pushButton_ToLogFile = new QPushButton(centralwidget);
        pushButton_ToLogFile->setObjectName("pushButton_ToLogFile");

        verticalLayout_2->addWidget(pushButton_ToLogFile);


        horizontalLayout_2->addLayout(verticalLayout_2);


        verticalLayout->addLayout(horizontalLayout_2);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_AddSoldItem->setText(QCoreApplication::translate("MainWindow", "AddSoldItem", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_dbtest->setText(QCoreApplication::translate("MainWindow", "DBtest", nullptr));
        groupBox_Import->setTitle(QCoreApplication::translate("MainWindow", "T\303\266rzs Import", nullptr));
        pushButton_PartnerImport->setText(QCoreApplication::translate("MainWindow", "Partner Import", nullptr));
        pushButton_AddressImport->setText(QCoreApplication::translate("MainWindow", "C\303\255m Import", nullptr));
        pushButton_TetelImport->setText(QCoreApplication::translate("MainWindow", "T\303\251tel Import", nullptr));
        pushButton_ToClipBoard->setText(QCoreApplication::translate("MainWindow", "ToClipBoard", nullptr));
        pushButton_ToLogFile->setText(QCoreApplication::translate("MainWindow", "ToLogFile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
