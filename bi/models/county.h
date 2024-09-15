#ifndef COUNTY_H
#define COUNTY_H

#include "bi/meta/meta.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <dataform.h>

class County
{
public:
    County();
    County(int i, const QString& n, const QString& k);

    int id=-1;
    QString countyName;
    QString KSHCode;


public:
    bool isValid();

    // meta
private:
    static Meta<County> _meta;
public:
    static void MetaInit();    
    // sqlrepo
    // home/zoli/source/repos/biovitality/bi/repositories/sqlrepository.cpp
    // template class SqlRepository<County>;
    //
    // static void MetaInit(){ ...
    // County::MetaInit();
    //
    // home/zoli/source/repos/biovitality/bi/repositories/sqlrepository.cpp
    // template class SqlRepository<County>;

    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    static County FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

// DataForm
    IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }
    static DataRowDefaultModel To_DataRowDefaultModel(const QList<County>& data)
    {
        return _meta.ToIdMegnevs(data);
    }

};

#endif // COUNTY_H
