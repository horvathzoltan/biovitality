#include "county.h"

#include <meta/csvhelper.h>

MetaData<County> County::_meta;
// QList<County> County::_data = {
//     {5,"Budapest","01"},
//     {2,"Baranya vármegye","02"},
//     {1,"Bács-Kiskun vármegye","03"},
//     {3,"Békés vármegye","04"},
//     {4,"Borsod-Abaúj-Zemplén vármegye","05"},
//     {6,"Csongrád-Csanád vármegye","06"},
//     {7,"Fejér vármegye","07"},
//     {8,"Győr-Moson-Sopron vármegye","08"},
//     {9,"Hajdú-Bihar vármegye","09"},
//     {10,";Heves vármegye","10"},
//     {12,";Komárom-Esztergom vármegye","11"},
//     {13,";Nógrád vármegye","12"},
//     {14,";Pest vármegye","13"},
//     {20,";Somogy vármegye","14"},
//     {15,";Szabolcs-Szatmár-Bereg vármegye","15"},
//     {11,";Jász-Nagykun Szolnok vármegye","16"},
//     {16,";Tolna vármegye","17"},
//     {17,";Vas vármegye","18"},
//     {18,";Veszprém vármegye","19"},
//     {19,";Zala vármegye","20"}
// };


void County::MetaInit()
{
    AddMetaBase(County);
    AddMetaField(id); // id
    AddMetaField(countyName); //megnev
    AddMetaField(KSHCode); //code

    _meta.MetaIdMegnevIndex(0,{1},2);
    //AddMetaIdMegnevIndex(id, name, KSH_code);

}

void County::AddRefs(){};
void County::DeleteRefs(){};

bool County::isValid()
{
    if(id<0) return false;
    if(countyName.isEmpty()) return false;
    return true;
}

// DataRowDefaultModel County::To_DataRowDefaultModel(const QList<County>& data)
// {
//     DataRowDefaultModel e;
//     e.name = _meta._baseName;

//     for(auto&a:data){
//         IdMegnev i = a.ToIdMegnev();
//         e.values.append(i);
//     }

//     return e;
// }

County::County() {}

County::County(int i, const QString &n, const QString &k)
{
    id = i; countyName = n; KSHCode = k;
}

CSV_ImportModel<County> County::CSV_Import(const QList<QVarLengthArray<QString>>& records,
                                           const QChar& separator)
{
    CSV_ImportModel<County> m;

    int L = records.length();

    CSVHelper::RowToField ixln;
    AddRowToField(ixln, countyName, "Megye");
    AddRowToField(ixln, KSHCode, "KSHkód");

    QMap<QString,int> ixs = ixln.Get_RowIndexes(records[0]);

    for(int i = 1;i<L;i++){
        QVarLengthArray<QString> row = records[i];

        QList<MetaValue> metaValues = CSVHelper::CSV_RowToMetaValues(row, ixs);
        County item = County::Meta().FromMetaValues(metaValues);
        item.id = 0;

        CSV_ImportModel<County>::Data data(item, row, i, separator);
        m.Add(data);

        // bool valid = item.isValid();
        // if(valid){
        //     m.append(item);
        // } else{
        //     zInfo("invalid row:"+QString::number(i+1)+" row:"+QString::number(i));
        // }
    }

    return m;

    return m;
}
