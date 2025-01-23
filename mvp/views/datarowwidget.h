#ifndef DATAROWWIDGET_H
#define DATAROWWIDGET_H

#include <QLabel>
#include <QLineEdit>
#include <QSpacerItem>
#include <QTimer>
#include <QWidget>

#include <meta/meta.h>

class DataRowWidget: public QWidget
{
    Q_OBJECT

private:
    QLabel* _label;
    QLineEdit* _edit;
    QLabel* _idLabel;
    QLabel* _validateLabel;
    QSpacerItem* _spacer;
    MetaValue _metaValue {"", "", QMetaType(), RefType::None};
    QList<IdMegnev> _defaultValues;    
    QTimer _editTimer;
    //int _autoCompleteMillisec;
    static QString ToString(const QSet<QChar>& chars);
    static QSet<QChar> Talalat(const QList<IdMegnev>& a, int L);
    static QSet<QChar> Talalat2(const QList<IdMegnev>& a, const QString&txt);
public:
    DataRowWidget(const MetaValue& m, int w,bool isLight, int autoCompleteMillisec);
    MetaValue metaValue(){return _metaValue;}
    QVariant value();
    QString text();
    void SetValidateLabel(const QString& v){_validateLabel->setText(v);}
    ~DataRowWidget();

    QString name(){return _metaValue.metaField_name;}
    void SetDataRowDefault(const QList<IdMegnev>& v);

    // QStringList GetDefaultValue_ByName_Start(const QString& txt);
    // QStringList GetDefaultValue_ByName_Contains(const QString& txt);
    // QStringList GetDefaultValue_ByCode(const QString& txt);
    // QList<int> GetDefaultId_ByCode(const QString &txt);

    void SetIdMegnev(const IdMegnev& v);

    QList<IdMegnev> GetDefault_ByName_Start(const QString& txt);
    QList<IdMegnev> GetDefault_ByName_Contains(const QString& txt);
    QList<IdMegnev> GetDefault_ByCode(const QString& txt);

private slots:
    void on_textEdited(const QString &text);
    void on_timeout();
};

#endif // DATAROWWIDGET_H
