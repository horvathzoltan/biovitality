#ifndef ARTICLE_H
#define ARTICLE_H

#include "meta/meta.h"
#include "modelinterfaces.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <mvp/views/dataform.h>

//DataForm
class Article : I_Meta<Article>
    , I_SQLRepo_Read<Article>
    , I_SQLRepo_CreateUpdate<Article>
    , I_CSVImport<Article>
{
public:
    Article();
    Article(int i, const QString& n, const QString& k, int e);

    int id=-1;
    QString Name;
    QString Barcode;
    int excelId=-1;

    // Meta
private:
    static Meta<Article> _meta;    
public:        
    bool isValid();
    static void MetaInit();
    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}

    // SQL_Read
    static QString GetMetaFieldNames(){ return _meta.GetMetaFieldNames();}
    static Article FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}

    // SQL_Create,Update
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

// DataForm
    static DataRowDefaultModel To_DataRowDefaultModel(const QList<Article>& data)
    {
        return _meta.ToIdMegnevs(data);
    }
    IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }

};

#endif // ARTICLE_H
