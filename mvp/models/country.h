#ifndef COUNTRY_H
#define COUNTRY_H

#include "meta/meta.h"
#include <QString>


class Country
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
    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}
    // ez a modellbe mapol név szerint
    static Country FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
    // CSV import
    static QList<Country> CSV_Import(const QList<QVarLengthArray<QString>>& records);
};

#endif // COUNTRY_H
