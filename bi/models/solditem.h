#ifndef SOLDITEM_H
#define SOLDITEM_H

#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>

struct MetaField{
public:
    QString name;
};

class Meta{
    bool _isInited = false;
    QList<MetaField> _fields;
public:
    void Init();
    void AddField(const QString& name);
    QString GetFieldList();
};

class SoldItem
{
public:
    SoldItem();

    int id;
    QString partnerName;
    QString partnerHq;
    QString county;
    QDate fullfillment;
    QString accountNr;
    QString productName;
    int units=-1;
    qreal unitPrice=0;
    QString unitCurrency;
    qreal netPrice=0;
    QString netCurrency;

    // struct PriceModel{
    //     qreal amount=0;
    //     QString currency="";
    // };

    static Meta _meta;
    static QList<SoldItem> ImportCSV(const QList<QVarLengthArray<QString>>& records);
    static QVariant GetData(const QVarLengthArray<QString>& row, int ix);
    static QVariant GetData(const QVarLengthArray<QString>& row, const QString &columnName, const QMap<QString, int>& ixs);
    bool isValid();
    //static PriceModel GetPrice(const QVariant& v);
    static qreal GetPrice2(const QVariant& v, const QLocale& locale);
    static int GetId(const QVariant& v);


private:
    static int indexOf(const QVarLengthArray<QString>& row, const QString & column_name);
};

#endif // SOLDITEM_H
