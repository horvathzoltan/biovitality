#ifndef COUNTRY_H
#define COUNTRY_H

#include "meta/meta.h"
#include <QString>

class ISQLRepo{
    virtual QVariant GetValue(const QString& name) const =0;
    // virtual MetaField* GetField(const QString& name) const =0;
    // virtual QString GetMetaFieldList() =0;
    virtual QList<SQLHelper::SQLParam> GetQueryParams() const = 0;
};

template<typename T>
class ICSVImport{
    virtual QList<T> CSV_Import(const QList<QVarLengthArray<QString>>& records){return T::CSV_Import_static(records);}
    //virtual T FromMetaValues(const QList<MetaValue> &v) =0;
};

class Country : ISQLRepo, ICSVImport<Country>
{
public:
    Country();

    int id=-1;
    QString name;
    //ccTLD
    // https://www.iana.org/domains/root/db
    // https://github.com/lukes/ISO-3166-Countries-with-Regional-Codes/blob/master/all/all.csv
    // https://en.wikipedia.org/wiki/ISO_3166-1_alpha-2
    QString alpha2;
    // https://en.wikipedia.org/wiki/ISO_3166-1_alpha-3
    //QString alpha3;
    // https://en.wikipedia.org/wiki/ISO_3166-1_numeric
    int countryCode=0;

    bool isValid();

    // meta
private:
    static Meta<Country> _meta;
public:
    static void MetaInit();

    // sqlrepohoz kell
    QVariant GetValue(const QString& name) const override { return _meta.GetValue(this, name);}
    static MetaField* GetField(const QString& name) {return _meta.GetField(name);}
    // sqlrepohoz kell
    static QString GetMetaFieldList() { return _meta.GetFieldList();}
    QList<SQLHelper::SQLParam> GetQueryParams()const override { return _meta.ToMetaValues2(this);}

    // CSV import
    static QList<Country> CSV_Import_static(const QList<QVarLengthArray<QString>>& records);
    // ez a modellbe mapol név szerint
    static Country FromMetaValues(const QList<MetaValue> &v) {return _meta.FromMetaValues(v);}
};

#endif // COUNTRY_H
