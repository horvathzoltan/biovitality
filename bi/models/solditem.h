#ifndef SOLDITEM_H
#define SOLDITEM_H

#include "bi/meta/meta.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

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
    int excelId=-1;

    bool isValid();

    // meta
private:
    static Meta<SoldItem> _meta;
public:
    static void MetaInit();
    // sqlrepo
    // /home/zoli/source/repos/biovitality/globals.h
    // Repositories() ... ,sr("SoldItem") ... {}
    // SqlRepository<SoldItem> sr;
    //
    // static void MetaInit(){ ...
    // SoldItem::MetaInit();
    //
    // home/zoli/source/repos/biovitality/bi/repositories/sqlrepository.cpp
    // template class SqlRepository<SoldItem>;

    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    //static QString GetMetaFieldList_UPDATE(){ return _meta.GetFieldList_UPDATE();}
    static SoldItem FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
    QList<MetaValue> GetMetaValues()const { return _meta.ToMetaValues(this);}
    QString GetBaseTypeName() {return _meta.GetBaseTypeName();}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

public:
// CSV import
    static QList<SoldItem> CSV_Import(const QList<QVarLengthArray<QString>>& records);

public:

    //static PriceModel GetPrice(const QVariant& v);
    static qreal GetPrice2(const QVariant& v, const QLocale& locale);


};

#endif // SOLDITEM_H
