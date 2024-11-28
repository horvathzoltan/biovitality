#ifndef COUNTRY_H
#define COUNTRY_H

#include "meta/meta.h"
#include "modelinterfaces.h"
#include <QString>

class Country : I_Meta<Country>
    , I_SQLRepo_Read<Country>
    , I_SQLRepo_CreateUpdate<Country>
    , I_CSVImport<Country>
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

    // Meta
private:
    static Meta<Country> _meta;
public:
    bool isValid();
    static void MetaInit();           
    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}

    // SQL_Read
    static QString GetMetaFieldNames() { return _meta.GetMetaFieldNames();}
    static Country FromMetaValues(const QList<MetaValue> &v) {return _meta.FromMetaValues(v);}

    // SQL_Create,Update
    QList<SQLHelper::SQLParam> GetQueryParams()const  { return _meta.ToMetaValues2(this);}

    // CSV import
    static QList<Country> CSV_Import(const QList<QVarLengthArray<QString>>& records);
    QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}
    static MetaField* GetMetaField(const QString& name) {return _meta.GetMetaField(name);}

};


#endif // COUNTRY_H

