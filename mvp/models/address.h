#ifndef ADDRESS_H
#define ADDRESS_H

#include "meta/meta.h"
#include <QVariant>

class Address
{
public:
    Address();

    int id=-1;
    int countryId;      // ref a country-ra az id-n keresztül
    int postalCode;         // irsz
    QString settlementName; // településnév
    QString publicAreaName; // közterület(utca) név + házszám - a cím utolsó tagja
    //QString houseNumber;  // házszám - a cím utolsó tagja
    int excelId=-1;

    bool isValid();

    // meta
private:
    static Meta<Address> _meta;
public:
    static void MetaInit();
    // sqlrepo
    // home/zoli/source/repos/biovitality/bi/repositories/sqlrepository.cpp
    // template class SqlRepository<Address>;
    //
    // static void MetaInit(){ ...
    // Address::MetaInit();
    //
    // home/zoli/source/repos/biovitality/bi/repositories/sqlrepository.cpp
    // template class SqlRepository<Address>;

    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    //static QString GetMetaFieldList_UPDATE(){ return _meta.GetFieldList_UPDATE();}
    static Address FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
    QList<MetaValue> GetMetaValues()const { return _meta.ToMetaValues(this);}
    QString GetBaseTypeName() {return _meta.GetBaseTypeName();}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}
    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}

// CSV import
    static QList<Address> CSV_Import(const QList<QVarLengthArray<QString>>& records);

// DataForm
    static DataRowDefaultModel To_DataRowDefaultModel(const QList<Address>& data)
    {
        return _meta.ToIdMegnevs(data);
    }
    IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }
private:
    void Parse(const QString& c);
};

#endif // ADDRESS_H
