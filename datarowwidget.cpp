#include "datarowwidget.h"

#include <QLayout>

DataRowWidget::DataRowWidget(const QString &label)
{
    QColor color1 = Qt::green;//status?Qt::green:Qt::red;
    QPalette pal1 = QPalette();

    int l1_width = 100;
    int height = 20;
    QHBoxLayout *lay= new QHBoxLayout();
    lay->setGeometry(QRect(0, 0, l1_width+10, height+10));
    lay->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    lay->setSpacing(0);
    //lay->setMargin(0);


    //setMinimumHeight(height+10);
    //setMinimumWidth(l1_width+10);
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    //this->setColor(_label->backgroundRole(), color1);


    _label = new QLabel();
    QFont f1 = _label->font();
    f1.setPointSize(10);
    _label->setFont(f1);
    _label->setText(label);

    _label->setGeometry(QRect(0, 0, l1_width, height));
    _label->setMinimumSize(l1_width, height);
    _label->setMaximumSize(l1_width, height);


    _label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _label->setAlignment(Qt::AlignTop|Qt::AlignLeft);

    _label->setAutoFillBackground(true);

    pal1.setColor(_label->backgroundRole(), color1);

    lay->addWidget(_label);

    // widget
    setMinimumSize(l1_width+10, height+10);
    setMaximumSize(l1_width+10, height+10);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setLayout( lay );

    setGeometry(QRect(0, 0, l1_width+10, height+10));

    //_label->show();
}

DataRowWidget::~DataRowWidget()
{
    delete(_label);
}
