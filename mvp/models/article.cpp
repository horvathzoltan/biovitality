#include "article.h"

#include <meta/csvhelper.h>

MetaData<Article> Article::_meta;

Article::Article() {
    //alimedCode = QVariant(QMetaType(QMetaType::ULongLong));
}

// Article::Article(int i, const QString &n, const QString &k, int e)
// {
//     id = i; Name = n; Barcode = k; //excelId = e;
// }

void Article::MetaInit()
{
    AddMetaBase(Article);
    AddMetaField(id); // id
    AddMetaField(Name); //megnev
    AddMetaField(Barcode); //code
    AddMetaField(alimedCode); //code

    //FieldType fieldType;
    //fieldType.declType = QMetaType::fromType<decltype(_meta._instance.alimedCode)>();//QMetaType::fromType<QVariant>();
    //fieldType.valueType = _meta._instance.alimedCode.metaType();

    AddMetaField(ogyeiCode); //code
    //AddMetaField(excelId); //excelId

    // 1+2+3
    //_meta.MetaIdMegnevIndex(0,{1},2);

    _meta.SetMetaIdMegnev(Article, id, Name);
    _meta.AddCode(Article, Barcode);
}

void Article::AddRefs(){};
void Article::DeleteRefs(){};

bool Article::isValid()
{
    if(id<0) return false;
    if(Name.isEmpty()) return false;
    return true;
}

CSV_ImportModel<Article> Article::CSV_Import(const QList<QVarLengthArray<QString>>& records,
                                                        const QChar& separator)
{
    CSV_ImportModel<Article> m;

    int L = records.length();

    CSVHelper::RowToField ixln;
    AddRowToField(ixln, Name, "Termék neve");
    AddRowToField(ixln, Barcode, "Vonalkód");
    AddRowToField(ixln, alimedCode, "ALIMED kódja");
    AddRowToField(ixln, ogyeiCode, "OGYÉI eng.sz.");
    //AddRowToField(ixln, excelId, "ID");

    QMap<QString,int> ixs = ixln.Get_RowIndexes(records[0]);

    for(int i = 1;i<L;i++){
        QVarLengthArray<QString> row = records[i];

        QList<MetaValue> metaValues = CSVHelper::CSV_RowToMetaValues(row, ixs);
        Article item = Article::Meta().FromMetaValues(metaValues);
        item.id = 0;

        CSV_ImportModel<Article>::Data data(item, row, i, separator);
        m.Add(data);
        // bool valid = item.isValid();
        // if(valid){
        //     m.append(item);
        // } else{
        //     zInfo("invalid row: "+QString::number(i+1)+" row: "+QString::number(i));
        // }
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
