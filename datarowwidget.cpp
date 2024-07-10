#include "datarowwidget.h"

#include <QLayout>

DataRowWidget::DataRowWidget(const QString &label)
{
    _label = new QLabel();
    _label->setMinimumHeight(20);
    _label->setMinimumWidth(100);
    _label->setBackgroundRole(QPalette::Base);
    _label->setAutoFillBackground(true);

    _label->setText(label);

    //QLayout *layout = this->layout();
    //layout->addWidget(_label);
}

DataRowWidget::~DataRowWidget()
{
    delete(_label);
}
