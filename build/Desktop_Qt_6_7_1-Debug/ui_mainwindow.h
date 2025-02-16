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
    QLabel *label;
    QPushButton *pushButton_dbtest;
    QSpacerItem *horizontalSpacer;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_AddSoldItem;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_TetelImport;
    QGroupBox *groupBox_Import;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_ArticleImport;
    QPushButton *pushButton_CoutntyImport;
    QPushButton *pushButton_CountryImpot;
    QGroupBox *groupBox_Address;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_AddressList;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_AddressImport;
    QGroupBox *groupBox_Partner;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *pushButton_PartnerList;
    QSpacerItem *horizontalSpacer_5;
    QPushButton *pushButton_PartnerImport;
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
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        pushButton_dbtest = new QPushButton(centralwidget);
        pushButton_dbtest->setObjectName("pushButton_dbtest");

        horizontalLayout->addWidget(pushButton_dbtest);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName("groupBox");
        horizontalLayout_3 = new QHBoxLayout(groupBox);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        pushButton_AddSoldItem = new QPushButton(groupBox);
        pushButton_AddSoldItem->setObjectName("pushButton_AddSoldItem");

        horizontalLayout_3->addWidget(pushButton_AddSoldItem);

        horizontalSpacer_3 = new QSpacerItem(769, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        pushButton_TetelImport = new QPushButton(groupBox);
        pushButton_TetelImport->setObjectName("pushButton_TetelImport");

        horizontalLayout_3->addWidget(pushButton_TetelImport);


        verticalLayout->addWidget(groupBox);

        groupBox_Import = new QGroupBox(centralwidget);
        groupBox_Import->setObjectName("groupBox_Import");
        horizontalLayout_4 = new QHBoxLayout(groupBox_Import);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButton_ArticleImport = new QPushButton(groupBox_Import);
        pushButton_ArticleImport->setObjectName("pushButton_ArticleImport");

        horizontalLayout_4->addWidget(pushButton_ArticleImport);

        pushButton_CoutntyImport = new QPushButton(groupBox_Import);
        pushButton_CoutntyImport->setObjectName("pushButton_CoutntyImport");

        horizontalLayout_4->addWidget(pushButton_CoutntyImport);

        pushButton_CountryImpot = new QPushButton(groupBox_Import);
        pushButton_CountryImpot->setObjectName("pushButton_CountryImpot");

        horizontalLayout_4->addWidget(pushButton_CountryImpot);


        verticalLayout->addWidget(groupBox_Import);

        groupBox_Address = new QGroupBox(centralwidget);
        groupBox_Address->setObjectName("groupBox_Address");
        horizontalLayout_5 = new QHBoxLayout(groupBox_Address);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        pushButton_AddressList = new QPushButton(groupBox_Address);
        pushButton_AddressList->setObjectName("pushButton_AddressList");

        horizontalLayout_5->addWidget(pushButton_AddressList);

        horizontalSpacer_4 = new QSpacerItem(761, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);

        pushButton_AddressImport = new QPushButton(groupBox_Address);
        pushButton_AddressImport->setObjectName("pushButton_AddressImport");

        horizontalLayout_5->addWidget(pushButton_AddressImport);


        verticalLayout->addWidget(groupBox_Address);

        groupBox_Partner = new QGroupBox(centralwidget);
        groupBox_Partner->setObjectName("groupBox_Partner");
        horizontalLayout_6 = new QHBoxLayout(groupBox_Partner);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        pushButton_PartnerList = new QPushButton(groupBox_Partner);
        pushButton_PartnerList->setObjectName("pushButton_PartnerList");

        horizontalLayout_6->addWidget(pushButton_PartnerList);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_5);

        pushButton_PartnerImport = new QPushButton(groupBox_Partner);
        pushButton_PartnerImport->setObjectName("pushButton_PartnerImport");

        horizontalLayout_6->addWidget(pushButton_PartnerImport);


        verticalLayout->addWidget(groupBox_Partner);

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
        label->setText(QCoreApplication::translate("MainWindow", "TextLabel", nullptr));
        pushButton_dbtest->setText(QCoreApplication::translate("MainWindow", "DBtest", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "T\303\251tel", nullptr));
        pushButton_AddSoldItem->setText(QCoreApplication::translate("MainWindow", "Hozz\303\241ad\303\241s", nullptr));
        pushButton_TetelImport->setText(QCoreApplication::translate("MainWindow", "Import", nullptr));
        groupBox_Import->setTitle(QCoreApplication::translate("MainWindow", "MainDataImport", nullptr));
        pushButton_ArticleImport->setText(QCoreApplication::translate("MainWindow", "ArticleImport", nullptr));
        pushButton_CoutntyImport->setText(QCoreApplication::translate("MainWindow", "CountyImport", nullptr));
        pushButton_CountryImpot->setText(QCoreApplication::translate("MainWindow", "CountryImport", nullptr));
        groupBox_Address->setTitle(QCoreApplication::translate("MainWindow", "address", nullptr));
        pushButton_AddressList->setText(QCoreApplication::translate("MainWindow", "AddressList", nullptr));
        pushButton_AddressImport->setText(QCoreApplication::translate("MainWindow", "AddressImport", nullptr));
        groupBox_Partner->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        pushButton_PartnerList->setText(QCoreApplication::translate("MainWindow", "PartnerList", nullptr));
        pushButton_PartnerImport->setText(QCoreApplication::translate("MainWindow", "PartnerImport", nullptr));
        pushButton_ToClipBoard->setText(QCoreApplication::translate("MainWindow", "ToClipBoard", nullptr));
        pushButton_ToLogFile->setText(QCoreApplication::translate("MainWindow", "ToLogFile", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
