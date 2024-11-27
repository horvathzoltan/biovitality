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

class Partner : I_Meta<Partner>, I_SQLRepo<Partner>, I_CSVImport<Partner>
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

    QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}
    static MetaField* GetField(const QString& name) {return _meta.GetField(name);}
    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

    QList<MetaValue> GetMetaValues()const { return _meta.ToMetaValues(this);}
    QString GetBaseTypeName() {return _meta.GetBaseTypeName();}

    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}

    // CSV import
    static QList<Partner> CSV_Import(const QList<QVarLengthArray<QString>>& records);
    // ez a modellbe mapol név szerint
    static Partner FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
    // DataForm
    static DataRowDefaultModel To_DataRowDefaultModel(const QList<Partner>& data)
    {
        return _meta.ToIdMegnevs(data);
    }
    IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }
};

#endif // PARTNER_H
