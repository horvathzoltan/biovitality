#ifndef ADDRESS_H
#define ADDRESS_H

#include "meta/meta.h"
#include "modelinterfaces.h"
#include <QVariant>

class Address : I_Meta<Address>, I_SQLRepo<Address>, I_CSVImport<Address>
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

    QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}
    static MetaField* GetField(const QString& name) {return _meta.GetField(name);}
    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

    //static QString GetMetaFieldList_UPDATE(){ return _meta.GetFieldList_UPDATE();}

    QList<MetaValue> GetMetaValues()const { return _meta.ToMetaValues(this);}
    QString GetBaseTypeName() {return _meta.GetBaseTypeName();}

    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}

// CSV import
    static QList<Address> CSV_Import(const QList<QVarLengthArray<QString>>& records);
// SQL_Repo
    static Address FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
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
