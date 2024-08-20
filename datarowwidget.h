#ifndef DATAROWWIDGET_H
#define DATAROWWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>
#include <QTimer>
#include <QWidget>

#include <bi/meta/meta.h>

class DataRowWidget: public QWidget
{
    Q_OBJECT

private:
    QLabel* _label;
    QLineEdit* _edit;
    QLabel* _validateLabel;
    QSpacerItem* _spacer;
    MetaValue _metaValue {"", "", QMetaType()};
    QList<IdMegnev> _defaultValues;    
    QTimer _editTimer;

public:
    DataRowWidget(const MetaValue& m, int w,bool isLight);
    MetaValue metaValue(){return _metaValue;}
    QVariant value();
    QString text();
    void SetValidateLabel(const QString& v){_validateLabel->setText(v);}
    ~DataRowWidget();

    QString name(){return _metaValue.name;}
    void SetDataRowDefault(const QList<IdMegnev>& v){_defaultValues = v;}

    QStringList GetDefaultValue_ByName_Start(const QString& txt);
    QStringList GetDefaultValue_ByName_Contains(const QString& txt);
    QStringList GetDefaultValue_ByCode(const QString& txt);

private slots:
    void on_textEdited(const QString &text);
    void on_timeout();
};

#endif // DATAROWWIDGET_H
