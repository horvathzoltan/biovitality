#include "datarowwidget.h"
#include "helpers/stringhelper.h"

#include <QLayout>

DataRowWidget::DataRowWidget(const MetaValue &m, int w, bool isLight, int autoCompleteMillisec)
{
    _metaValue = m;

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

    _edit->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    _edit->setAlignment(Qt::AlignVCenter|Qt::AlignLeft);

    _edit->setAutoFillBackground(true);

    _edit->connect(_edit, &QLineEdit::textEdited, this, &DataRowWidget::on_textEdited ); //textEdited, this, on_textEdited);
    _validateLabel = new QLabel();
    f1 = _validateLabel->font();
    f1.setPointSize(10);
    _validateLabel->setFont(f1);

    _validateLabel->setGeometry(QRect(0, 0, l1_width, height));
    _validateLabel->setMinimumSize(l1_width, height);
    //_validateLabel->setMaximumSize(l1_width, height);

    _validateLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    _validateLabel->setAlignment(Qt::AlignVCenter|Qt::AlignRight);

    // spacer
    _spacer = new QSpacerItem(1,1, QSizePolicy::Expanding, QSizePolicy::Fixed);

    lay->addWidget(_label);
    lay->addWidget(_edit);
    lay->addWidget(_validateLabel);
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

    _editTimer.setInterval(autoCompleteMillisec);
    _editTimer.setSingleShot(true);
    connect(&_editTimer, &QTimer::timeout, this, &DataRowWidget::on_timeout);
    //_label->show();
}

QVariant DataRowWidget::value()
{
    if(_edit == nullptr) return QVariant();
    QString txt = _edit->text();
    QVariant v(txt);
    return v;
}

QString DataRowWidget::text()
{
    if(_edit == nullptr) return QString();
    QString txt = _edit->text();
    return txt;
}

DataRowWidget::~DataRowWidget()
{
    delete(_label);
    delete(_edit);
    delete(_validateLabel);
    delete(_spacer);
}

void DataRowWidget::on_textEdited(const QString &text){
    zTrace();
    if(text.length()>0){
        _editTimer.start();
    }
}

void DataRowWidget::on_timeout()
{
    zTrace();
    QString txt = _edit->text();
    QStringList a = GetDefaultValue_ByCode(txt);
    if(a.length()==1){
        _edit->setText(a[0]);
    } else{
        if(txt.length()>=3){
            a = GetDefaultValue_ByName_Start(txt);
            if(a.length()==1){
                _edit->setText(a[0]);
            } else{
                a = GetDefaultValue_ByName_Contains(txt);
                if(a.length()==1){
                    _edit->setText(a[0]);
                }
            }
        }
    }
}

QStringList DataRowWidget::GetDefaultValue_ByName_Start(const QString &txt)
{
    if(txt.isEmpty()) return {};
    QString n_txt = StringHelper::Normalize(txt);
    QStringList m;
    for(auto&a:_defaultValues){
        QString b = StringHelper::Normalize(a.name);
        if(b.startsWith(n_txt)){
            m.append(a.name);
        }
    }
    return m;
}

QStringList DataRowWidget::GetDefaultValue_ByName_Contains(const QString &txt)
{
    if(txt.isEmpty()) return {};
    QString n_txt = StringHelper::Normalize(txt);
    QStringList m;
    for(auto&a:_defaultValues){
        QString b = StringHelper::Normalize(a.name);
        if(b.contains(n_txt)){
            m.append(a.name);
        }
    }
    return m;
}


QStringList DataRowWidget::GetDefaultValue_ByCode(const QString &txt)
{
    if(txt.isEmpty()) return {};
    QString n_txt = StringHelper::Normalize(txt);
    QStringList m;
    for(auto&a:_defaultValues){
        QString b = StringHelper::Normalize(a.code);
        if(b.startsWith(n_txt)){
            m.append(a.name);
        }
    }
    return m;
}
