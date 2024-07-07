/********************************************************************************
** Form generated from reading UI file 'dataform.ui'
**
** Created by: Qt User Interface Compiler version 6.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DATAFORM_H
#define UI_DATAFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_DataForm
{
public:
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *DataForm)
    {
        if (DataForm->objectName().isEmpty())
            DataForm->setObjectName("DataForm");
        DataForm->resize(400, 300);
        buttonBox = new QDialogButtonBox(DataForm);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(30, 240, 341, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        retranslateUi(DataForm);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, DataForm, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, DataForm, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(DataForm);
    } // setupUi

    void retranslateUi(QDialog *DataForm)
    {
        DataForm->setWindowTitle(QCoreApplication::translate("DataForm", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DataForm: public Ui_DataForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DATAFORM_H
