#include "datarowwidget.h"

DataRowWidget::DataRowWidget(const QString &label)
{
    _label = new QLabel();
    _label->setText(label);
}

DataRowWidget::~DataRowWidget()
{
    delete(_label);
}
