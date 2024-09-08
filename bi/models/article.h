#ifndef ARTICLE_H
#define ARTICLE_H

#include "bi/meta/meta.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <dataform.h>

class Article
{
public:
    Article();
    Article(int i, const QString& n, const QString& k, int e);

    int id=-1;
    QString Name;
    QString Barcode;
    int excelId=-1;

    static void MetaInit();

    bool isValid();

    //static DataRowDefaultModel To_DataRowDefaultModel(const QList<Article>& data);
    static DataRowDefaultModel To_DataRowDefaultModel(const QList<Article>& data)
    {
        return _meta.ToIdMegnevs(data);
    }
    IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }
    // sqlrepo
    // template class SqlRepository<Article>;
    static QString GetMetaFieldList(){ return _meta.GetFieldList();}
    static Article FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}
    QList<SQLHelper::SQLParam> GetQueryParams()const { return _meta.ToMetaValues2(this);}

private:
    static QList<Article> _data;
    static Meta<Article> _meta;
};

#endif // ARTICLE_H
