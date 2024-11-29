#include "article.h"

#include <meta/csvhelper.h>

Meta<Article> Article::_meta;

Article::Article() {}

Article::Article(int i, const QString &n, const QString &k, int e)
{
    id = i; Name = n; Barcode = k; excelId = e;
}

void Article::MetaInit()
{
    AddMetaBase(Article);
    AddMetaField(id); // id
    AddMetaField(Name); //megnev
    AddMetaField(Barcode); //code
    AddMetaField(excelId); //excelId

    // 1+2+3
    _meta.MetaIdMegnevIndex(0,{1},2);
}

bool Article::isValid()
{
    if(id<0) return false;
    if(Name.isEmpty()) return false;
    return true;
}

QList<Article> Article::CSV_Import(const QList<QVarLengthArray<QString>>& records)
{
    QList<Article> m;

    int L = records.length();

    CSVHelper::RowToField ixln;
    ixln.AddRowToField(Name, "Termék megnevezése");
    ixln.AddRowToField(Barcode, "Vonalkód");
    ixln.AddRowToField(excelId, "ID");

    QMap<QString,int> ixs = ixln.Get_RowIndexes(records[0]);

    for(int i = 1;i<L;i++){
        QVarLengthArray<QString> row = records[i];

        QList<MetaValue> metaValues = CSVHelper::CSV_RowToMetaValues(row, ixs);
        Article item = Article::FromMetaValues(metaValues);
        item.id = 0;

        bool valid = item.isValid();
        if(valid){
            m.append(item);
        } else{
            zInfo("invalid row:"+QString::number(i+1)+" row:"+QString::number(i));
        }
    }

    return m;
}


// DataRowDefaultModel Article::To_DataRowDefaultModel(const QList<Article>& data)
// {
//     DataRowDefaultModel e;
//     e.name = _meta._baseName;

//     //QList<County> data = _globals._repositories.cr.GetAll();

//     for(auto&a:data){
//         IdMegnev i = a.ToIdMegnev();
//         e.values.append(i);
//     }

//     return e;
// }
