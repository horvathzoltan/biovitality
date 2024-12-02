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


class SoldItem : I_Meta<SoldItem>
    , I_SQLRepo_Read<SoldItem>
    , I_SQLRepo_CreateUpdate<SoldItem>
    , I_CSVImport<SoldItem>
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

    // Meta
private:
    static Meta<SoldItem> _meta;
public:
    bool isValid();
    static void MetaInit();
    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}
    static SoldItem metaInstance(){return _meta._instance;}

// SQL_Read
    static QString GetMetaFieldNames(){ return _meta.GetMetaFieldNames();}
    static SoldItem FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}

// SQL_Create,Update
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

    // CSV import
    static QList<SoldItem> CSV_Import(const QList<QVarLengthArray<QString>>& records);
    QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}
    static MetaField* GetMetaField(const QString& name) {return _meta.GetMetaField(name);}

//UI
    QList<MetaValue> GetMetaValues()const { return _meta.ToMetaValues(this);}

    //QString GetBaseTypeName() {return _meta.GetBaseTypeName();}

    //static PriceModel GetPrice(const QVariant& v);
    static qreal GetPrice2(const QVariant& v, const QLocale& locale);


};

#endif // SOLDITEM_H
