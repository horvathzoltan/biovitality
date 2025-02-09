/********************************************************************************
** Form generated from reading UI file 'datalistform.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATALISTFORM_H
#define UI_DATALISTFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_DataListForm
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QTableWidget *tableWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_Insert;
    QPushButton *pushButton_Update;
    QSpacerItem *horizontalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DataListForm)
    {
        if (DataListForm->objectName().isEmpty())
            DataListForm->setObjectName("DataListForm");
        DataListForm->resize(960, 300);
        verticalLayout_2 = new QVBoxLayout(DataListForm);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label = new QLabel(DataListForm);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);


        verticalLayout_2->addLayout(horizontalLayout);

        tableWidget = new QTableWidget(DataListForm);
        tableWidget->setObjectName("tableWidget");
        tableWidget->setEditTriggers(QAbstractItemView::EditTrigger::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SelectionMode::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectionBehavior::SelectRows);
        tableWidget->verticalHeader()->setVisible(false);

        verticalLayout_2->addWidget(tableWidget);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        pushButton_Insert = new QPushButton(DataListForm);
        pushButton_Insert->setObjectName("pushButton_Insert");

        horizontalLayout_2->addWidget(pushButton_Insert);

        pushButton_Update = new QPushButton(DataListForm);
        pushButton_Update->setObjectName("pushButton_Update");

        horizontalLayout_2->addWidget(pushButton_Update);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        buttonBox = new QDialogButtonBox(DataListForm);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        horizontalLayout_2->addWidget(buttonBox);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(DataListForm);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DataListForm, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, DataListForm, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DataListForm);
    } // setupUi

    void retranslateUi(QDialog *DataListForm)
    {
        DataListForm->setWindowTitle(QCoreApplication::translate("DataListForm", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("DataListForm", "TextLabel", nullptr));
        pushButton_Insert->setText(QCoreApplication::translate("DataListForm", "Insert", nullptr));
        pushButton_Update->setText(QCoreApplication::translate("DataListForm", "Update", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataListForm: public Ui_DataListForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATALISTFORM_H
