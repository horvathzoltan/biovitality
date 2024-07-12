#include "datarowwidget.h"

#include <QLayout>

DataRowWidget::DataRowWidget(const QString &label, int w)
{
    //QColor color1 = Qt::green;//status?Qt::green:Qt::red;
    //QPalette pal1 = QPalette();
    int l1_width = w+10;
    int e1_width = 100;
    int height = 20;

    // layout
    QHBoxLayout *lay= new QHBoxLayout();
    //lay->setGeometry(QRect(0, 0, l1_width+e1_width+10, height+10));
    //lay->setAlignment(Qt::AlignTop|Qt::AlignLeft);
    lay->setSpacing(0);

    //label
    _label = new QLabel();
    QFont f1 = _label->font();
    f1.setPointSize(10);
    _label->setFont(f1);
    _label->setText(label);

    _label->setGeometry(QRect(0, 0, l1_width, height));
    _label->setMinimumSize(l1_width, height);
    _label->setMaximumSize(l1_width, height);

    _label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _label->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    _label->setAutoFillBackground(true);

    //_label.QFontMetrics.boundingRect

    //pal1.setColor(_label->backgroundRole(), color1);

    //LineEdit
    _edit = new QLineEdit();
    f1 = _label->font();
    f1.setPointSize(10);
    _edit->setFont(f1);
    _edit->setText("platty");

    _edit->setGeometry(QRect(0, 0, e1_width, height));
    _edit->setMinimumSize(e1_width, height);
    _edit->setMaximumSize(e1_width, height);

    _edit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _edit->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);

    _edit->setAutoFillBackground(true);


    lay->addWidget(_label);
    lay->addWidget(_edit);

    // widget
    //setMinimumSize(l1_width+e1_width+10, height+10);
    //setMaximumSize(l1_width+e1_width+10, height+10);
    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    setLayout( lay );

    setGeometry(QRect(0, 0, l1_width+e1_width+10, height+10));
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);

    //_label->show();
}

DataRowWidget::~DataRowWidget()
{
    delete(_label);
}
