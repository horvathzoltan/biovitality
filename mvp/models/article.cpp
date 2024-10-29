#include "article.h"

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

    _meta.MetaIdMegnevIndex(0,{1},2);
    //AddMetaIdMegnevIndex(id, name, KSH_code);
}

bool Article::isValid()
{
    if(id<0) return false;
    if(Name.isEmpty()) return false;
    return true;
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
