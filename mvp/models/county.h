#ifndef COUNTY_H
#define COUNTY_H

#include "meta/meta.h"
#include "meta/csv_importmodel.h"
//#include "modelinterfaces.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include "helpers/filehelper.h"
#include "helpers/sqlhelper.h"

#include "mvp/views/dataform.h"

class County /*: I_Meta<County>
    , I_SQLRepo_Read<County>
    , I_SQLRepo_CreateUpdate<County>
    , I_CSVImport<County>*/
{
public:
    County();
    County(int i, const QString& n, const QString& k);

    int id=-1;
    QString countyName;
    QString KSHCode;

    // Meta
private:
    static MetaData<County> _meta;
public:
    static MetaData<County>& Meta(){return _meta;}
    bool isValid();
    static void MetaInit();
    static void AddRefs();
    static void DeleteRefs();


    //static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}
    //static County metaInstance(){return _meta._instance;}
    //static County* metaInstanceAddress(){return &_meta._instance;}

    // SQL_Read
    //static QString GetMetaFieldNames(){ return _meta.GetMetaFieldNames();}
    //static County FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}

    // SQL_CreateUpdate
    //QList<SQLHelper::SQLParam> ToSQLParams()const { return _meta.ToSQLParams(this);}

    // CSV import
    static CSV_ImportModel<County> CSV_Import(
        const QList<QVarLengthArray<QString>>& records,
        const QChar& separator);
    //QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}
    //static MetaField* GetMetaField(const QString& name) {return _meta.GetMetaField(name);}


// DataForm
    //IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }
    // static DataRowDefaultModel To_DataRowDefaultModel(const QList<County>& data)
    // {
    //     return _meta.ToIdMegnevs(data);
    // }

    //static int GetMetaFieldIx(const QString& v){ return _meta.GetMetaFieldIx(v);}
};

#endif // COUNTY_H
