#ifndef ADDRESS_H
#define ADDRESS_H

#include "meta/meta.h"
#include "modelinterfaces.h"
#include <QVariant>

class Address : I_Meta<Address>
    , I_SQLRepo_Read<Address>
    , I_SQLRepo_CreateUpdate<Address>
    , I_CSVImport<Address>
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

    // Meta
private:
    static Meta<Address> _meta;
public:
    bool isValid();
    static void MetaInit();
    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}

    // SQL_Read
    static QString GetMetaFieldNames(){ return _meta.GetMetaFieldNames();}
    static Address FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}

    // SQL_Create,Update
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

    // CSV import
    static QList<Address> CSV_Import(const QList<QVarLengthArray<QString>>& records);
    QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}    
    static MetaField* GetMetaField(const QString& name) {return _meta.GetMetaField(name);}

    //QString GetBaseTypeName() {return _meta.GetBaseTypeName();}

    //UI form viewModel
    QList<MetaValue> GetMetaValues()const { return _meta.ToMetaValues(this);}

// DataForm
    static DataRowDefaultModel To_DataRowDefaultModel(const QList<Address>& data)
    {
        return _meta.ToIdMegnevs(data);
    }
    IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }
private:
    void ParseAddressFields_private(const QString& c);
};

#endif // ADDRESS_H
