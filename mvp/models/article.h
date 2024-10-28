#ifndef ARTICLE_H
#define ARTICLE_H

#include "meta/meta.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <mvp/views/dataform.h>

class Article
{
public:
    Article();
    Article(int i, const QString& n, const QString& k, int e);

    int id=-1;
    QString Name;
    QString Barcode;
    int excelId=-1;

private:
    static Meta<Article> _meta;
    //static QList<Article> _data;

public:
    bool isValid();

// meta
    static void MetaInit();
    // sqlrepo
    // home/zoli/source/repos/biovitality/bi/repositories/sqlrepository.cpp
    // template class SqlRepository<Article>;
    //
    // static void MetaInit(){ ...
    // Article::MetaInit();
    //
    // home/zoli/source/repos/biovitality/bi/repositories/sqlrepository.cpp
    // template class SqlRepository<Article>;

    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    static Article FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

    static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}

// DataForm
    static DataRowDefaultModel To_DataRowDefaultModel(const QList<Article>& data)
    {
        return _meta.ToIdMegnevs(data);
    }
    IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }

};

#endif // ARTICLE_H
