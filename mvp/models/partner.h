#ifndef PARTNER_H
#define PARTNER_H

#include "meta/meta.h"
#include "modelinterfaces.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <mvp/views/dataform.h>

class Partner : I_Meta<Partner>
    , I_SQLRepo_Read<Partner>
    , I_SQLRepo_CreateUpdate<Partner>
    , I_CSVImport<Partner>
{
public:
    Partner();
    Partner(int i, const QString& n, int e);

    int id=-1;
    QString Name;
    int excelId=-1;

    // partnertipus // szállító/vevő/mindkettő
    // adózástípus
    // - Adószámmal rendelkezik (Belföldi ÁFA alany)
    // - Adószámmal nem rendelkezik (Természetes személy)
    // Külföldi, egyéb
    // Adószám
    // E-mail/ek
    // Telefonszám/ok
    // Bankszámlaszám
    // IBAN számlaszám
    // Swift / BIC kód
    // description
    // apiId

private:
    static Meta<Partner> _meta;

public:
    bool isValid();
    static void MetaInit();
    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}
    static Partner metaInstance(){return _meta._instance;}

    // SQL_Read
    static QString GetMetaFieldNames(){ return _meta.GetMetaFieldNames();}
    static Partner FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}

    // SQL_Create,Update
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

    // CSV import
    static CSV_ImportModel<Partner> CSV_Import(
        const QList<QVarLengthArray<QString>>& records,
        const QChar& separator);
    QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}
    static MetaField* GetMetaField(const QString& name) {return _meta.GetMetaField(name);}

    //QString GetBaseTypeName() {return _meta.GetBaseTypeName();}

    // ui
QList<MetaValue> GetMetaValues()const { return _meta.ToMetaValues(this);}
    // DataForm
    static DataRowDefaultModel To_DataRowDefaultModel(const QList<Partner>& data)
    {
        return _meta.ToIdMegnevs(data);
    }
    IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }
};

#endif // PARTNER_H
