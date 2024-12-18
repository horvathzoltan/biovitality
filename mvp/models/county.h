#ifndef COUNTY_H
#define COUNTY_H

#include "meta/meta.h"
#include "modelinterfaces.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <mvp/views/dataform.h>

class County : I_Meta<County>
    , I_SQLRepo_Read<County>
    , I_SQLRepo_CreateUpdate<County>
    , I_CSVImport<County>
{
public:
    County();
    County(int i, const QString& n, const QString& k);

    int id=-1;
    QString countyName;
    QString KSHCode;

    // Meta
private:
    static Meta<County> _meta;
public:
    bool isValid();
    static void MetaInit();
    static void AddRefs();
    static void DeleteRefs();


    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}
    static County metaInstance(){return _meta._instance;}
    static County* metaInstanceAddress(){return &_meta._instance;}

    // SQL_Read
    static QString GetMetaFieldNames(){ return _meta.GetMetaFieldNames();}
    static County FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}

    // SQL_CreateUpdate
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

    // CSV import
    static CSV_ImportModel<County> CSV_Import(
        const QList<QVarLengthArray<QString>>& records,
        const QChar& separator);
    QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}
    static MetaField* GetMetaField(const QString& name) {return _meta.GetMetaField(name);}


// DataForm
    IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }
    static DataRowDefaultModel To_DataRowDefaultModel(const QList<County>& data)
    {
        return _meta.ToIdMegnevs(data);
    }

    static int GetMetaFieldIx(const QString& v){ return _meta.GetMetaFieldIx(v);}
};

#endif // COUNTY_H
