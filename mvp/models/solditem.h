#ifndef SOLDITEM_H
#define SOLDITEM_H

#include "meta/meta.h"
#include "modelinterfaces.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

// enum MetaFieldListTypes{
//     Select, Update, Insert
// };


class SoldItem : I_Meta<SoldItem>, I_SQLRepo<SoldItem>, I_CSVImport<SoldItem>
{
public:
    SoldItem();

    int id=-1;
    QString partnerName; //partners
    QString partnerHq; //address
    QString county; // county
    QDate fullfillment;
    QString accountNr;
    QString productName; //article
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

    QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}
    static MetaField* GetField(const QString& name) {return _meta.GetField(name);}
    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

    QList<MetaValue> GetMetaValues()const { return _meta.ToMetaValues(this);}

    QString GetBaseTypeName() {return _meta.GetBaseTypeName();}

    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}
public:
// CSV import
    static QList<SoldItem> CSV_Import(const QList<QVarLengthArray<QString>>& records);
// SQL_Repo
    static SoldItem FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
public:

    //static PriceModel GetPrice(const QVariant& v);
    static qreal GetPrice2(const QVariant& v, const QLocale& locale);


};

#endif // SOLDITEM_H
