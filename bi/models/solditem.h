#ifndef SOLDITEM_H
#define SOLDITEM_H

#include "bi/meta/meta.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>

// enum MetaFieldListTypes{
//     Select, Update, Insert
// };

class SoldItem
{
public:
    SoldItem();

    int id=-1;
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

    static void MetaInit();

    static QList<SoldItem> ImportCSV(const QList<QVarLengthArray<QString>>& records);
    static QVariant GetData(const QVarLengthArray<QString>& row, int ix);
    static QVariant GetData(const QVarLengthArray<QString>& row, const QString &columnName, const QMap<QString, int>& ixs);
    bool isValid();
    //static PriceModel GetPrice(const QVariant& v);
    static qreal GetPrice2(const QVariant& v, const QLocale& locale);
    static int GetId(const QVariant& v);

    // meta

    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    static QString GetMetaFieldList_UPDATE(){ return _meta.GetFieldList_UPDATE();}

    static SoldItem FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
private:
    static Meta<SoldItem> _meta;

    static int indexOf(const QVarLengthArray<QString>& row, const QString & column_name);
};

#endif // SOLDITEM_H
