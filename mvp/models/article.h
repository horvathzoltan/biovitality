#ifndef ARTICLE_H
#define ARTICLE_H


//#include "modelinterfaces.h"
#include <QDateTime>
#include <QList>
#include <QVariant>

#include "helpers/filehelper.h"
#include "helpers/sqlhelper.h"

#include "meta/meta.h"
#include "meta/csv_importmodel.h"

#include "mvp/views/dataform.h"

#include "meta/csvhelper.h"

//DataForm
class Article /*: I_Meta<Article>
    , I_SQLRepo_Read<Article>
    , I_SQLRepo_CreateUpdate<Article>
    , I_CSVImport<Article>*/
{
public:
    Article();
   //Article(int i, const QString& n, const QString& k, int e);

    int id=-1;
    QString Name;
    QString Barcode;
    //QVariant alimedCode;
    std::optional<quint64> alimedCode;
    QString ogyeiCode;
    //int excelId=-1;

    // Meta
private:
    static MetaData<Article> _meta;
public:
    static MetaData<Article>& Meta(){return _meta;}
    bool isValid();
    static void MetaInit();
    static void AddRefs();
    static void DeleteRefs();


    //static void SetMetaVerbose(bool v){ _meta.SetVerbose(v);}
    //static Article metaInstance(){return _meta._instance;}
    //static Article* metaInstanceAddress(){return &_meta._instance;}
    // SQL_Read
    //static QString GetMetaFieldNames(){ return _meta.GetMetaFieldNames();}
    //static Article FromMetaValues(const QList<MetaValue> &v){return _meta.FromMetaValues(v);}

    // SQL_Create,Update
    //QList<SQLHelper::SQLParam> ToSQLParams()const { return _meta.ToSQLParams(this);}

    // CSV import
    static CSV_ImportModel<Article> CSV_Import(const QList<QVarLengthArray<QString>>& records,
                                               const QChar& separator);
    //QVariant GetValue(const QString& name) const { return _meta.GetValue(this, name);}
    //static MetaField* GetMetaField(const QString& name) {return _meta.GetMetaField(name);}

// DataForm
    // static DataRowDefaultModel To_DataRowDefaultModel(const QList<Article>& data)
    // {
    //     return _meta.ToIdMegnevs(data);
    // }
    //IdMegnev ToIdMegnev() const {return _meta.ToIdMegnev(this); }
};

#endif // ARTICLE_H
