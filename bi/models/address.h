#ifndef ADDRESS_H
#define ADDRESS_H

#include "bi/meta/meta.h"
#include "bi/meta/meta.h"
#include <QVariant>

class Address
{
public:
    Address();

    int id=-1;
    int postalCode;         // irsz
    QString settlementName; // településnév
    QString publicAreaName; // közterület(utca) név + házszám - a cím utolsó tagja
    //QString houseNumber;    // házszám - a cím utolsó tagja
    int excelId=-1;

    bool isValid();

    // meta
private:
    static Meta<Address> _meta;
public:
    static void MetaInit();
    // sqlrepo
    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    //static QString GetMetaFieldList_UPDATE(){ return _meta.GetFieldList_UPDATE();}
    static Address FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
    QList<MetaValue> GetMetaValues()const { return _meta.ToMetaValues(this);}
    QString GetBaseTypeName() {return _meta.GetBaseTypeName();}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

};

#endif // ADDRESS_H
