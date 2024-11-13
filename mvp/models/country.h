#ifndef COUNTRY_H
#define COUNTRY_H

#include "meta/meta.h"
#include <QString>

template<class T>
class I_Meta
{
public:
    I_Meta(){}
public:
    void __attribute__((used)) Check_I_Meta()
    {
        //Meta<T> *_meta_Check = &T::_meta;

        [[maybe_unused]] void (*MetaInit_Check)() = &T::MetaInit;
        [[maybe_unused]] bool (T::*isValid_Check)() = &T::isValid;
    }
};

 template<class T>
 class I_SQLRepo
{
public:
    I_SQLRepo(){}
public:
    void __attribute__((used)) Check_I_SQLRepo()
    {
        [[maybe_unused]] T (*FromMetaValues_Check)(const QList<MetaValue> &v) = &T::FromMetaValues;
        [[maybe_unused]] QList<T> (*CSV_Import_Check)(const QList<QVarLengthArray<QString>>& records) = &T::CSV_Import;
    }
};

template<class T>
class I_CSVImport{
public:
    I_CSVImport(){}
private:
    void __attribute__((used)) Check_I_CSVImport()
    {
        [[maybe_unused]] QVariant (T::*GetValue_Check)(const QString& name) const = &T::GetValue;
        [[maybe_unused]] MetaField* (*GetField_Check)(const QString& name) = &T::GetField;
        [[maybe_unused]] QString (*GetMetaFieldList_Check)() = &T::GetMetaFieldList;
        [[maybe_unused]] QList<SQLHelper::SQLParam> (T::*GetQueryParams_Check)()const = &T::GetQueryParams;
    }
};


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
    int countryCode=0;

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

