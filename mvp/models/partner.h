#ifndef PARTNER_H
#define PARTNER_H

#include "meta/meta.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <mvp/views/dataform.h>

class Partner
{
public:
    Partner();
    Partner(int i, const QString& n, int e);

    int id=-1;
    QString Name;
    int excelId=-1;

private:
    static Meta<Partner> _meta;

public:
    bool isValid();

    static void MetaInit();

    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    static Partner FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
    QList<MetaValue> GetMetaValues()const { return _meta.ToMetaValues(this);}
    QString GetBaseTypeName() {return _meta.GetBaseTypeName();}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}

    // CSV import
    static QList<Partner> CSV_Import(const QList<QVarLengthArray<QString>>& records);    
    // DataForm
    static DataRowDefaultModel To_DataRowDefaultModel(const QList<Partner>& data)
    {
        return _meta.ToIdMegnevs(data);
    }
    IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }
};

#endif // PARTNER_H
