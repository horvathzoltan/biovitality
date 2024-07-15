#include "datarowwidget.h"

#include <QLayout>

DataRowWidget::DataRowWidget(const MetaValue &m, int w, bool isLight)
{
    QColor color1 = Qt::green;//status?Qt::green:Qt::red;
    QColor color2 = Qt::darkGray;//status?Qt::green:Qt::red;
    QPalette pal = QPalette();
    int l1_width = w;
    int e1_width = 100;
    int height = 20;

    // layout
    QHBoxLayout *lay= new QHBoxLayout();
    lay->setGeometry(QRect(0, 0, l1_width+e1_width, height));
    lay->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);

    lay->setSpacing(2);
    lay->setContentsMargins(2,2,2,2);
    //label
    _label = new QLabel();
    QFont f1 = _label->font();
    f1.setPointSize(10);
    _label->setFont(f1);

    QString m_name = (!m.translatedName.isEmpty()?m.translatedName:m.wcode)+':';
    _label->setText(m_name);

    _label->setGeometry(QRect(0, 0, l1_width, height));
    _label->setMinimumSize(l1_width, height);
    _label->setMaximumSize(l1_width, height);

    _label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    _label->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    //_label.QFontMetrics.boundingRect
/*
    pal.setColor(_label->backgroundRole(), color1);
    _label->setPalette(pal);
    _label->setAutoFillBackground(true);
    _label->update();
*/
    //LineEdit
    _edit = new QLineEdit();
    f1 = _label->font();
    f1.setPointSize(10);
    _edit->setFont(f1);
    _edit->setText(m.value.toString());
    _edit->setFrame(false);

    _edit->setGeometry(QRect(0, 0, e1_width, height));
    _edit->setMinimumSize(e1_width, height);
    //_edit->setMaximumSize(e1_width, height);

    _edit->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _edit->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);

    _edit->setAutoFillBackground(true);

    // spacer
    _spacer = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);

    lay->addWidget(_label);
    lay->addWidget(_edit);
    lay->addSpacerItem(_spacer);
    // widget
    //setMinimumSize(l1_width+e1_width+10, height);
    //setMaximumSize(l1_width+e1_width+10, height);
    //setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
   setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    setLayout( lay );


    //setGeometry(QRect(0, 0, l1_width+e1_width+10, height));
    //setBackgroundRole(QPalette::Base);
    //setAutoFillBackground(true);
    if(isLight)
    {
        pal.setColor(backgroundRole(), color2);
        setPalette(pal);
        setAutoFillBackground(true);
        update();
    }

    //_label->show();
}

DataRowWidget::~DataRowWidget()
{
    delete(_label);
}
