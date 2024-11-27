#ifndef COUNTRY_H
#define COUNTRY_H

#include "meta/meta.h"
#include "modelinterfaces.h"
#include <QString>

class Country : I_Meta<Country>, I_SQLRepo<Country>, I_CSVImport<Country>
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
    int countryCode;

    bool isValid();

    // meta
private:
    static Meta<Country> _meta;
public:
    static void MetaInit();

    // sqlrepohoz kell
    QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}
    static MetaField* GetField(const QString& name) {return _meta.GetField(name);}
    static QString GetMetaFieldList() { return _meta.GetFieldList();}
    QList<SQLHelper::SQLParam> GetQueryParams()const  { return _meta.ToMetaValues2(this);}

    // CSV import
    static QList<Country> CSV_Import(const QList<QVarLengthArray<QString>>& records);
    // ez a modellbe mapol név szerint
    static Country FromMetaValues(const QList<MetaValue> &v) {return _meta.FromMetaValues(v);}
};


#endif // COUNTRY_H

