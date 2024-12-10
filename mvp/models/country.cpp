#include "country.h"

#include <meta/csvhelper.h>

#include <helpers/stringhelper.h>
#include "helpers/nameof.h"

Meta<Country> Country::_meta;

Country::Country(){}

void Country::MetaInit()
{
    AddMetaBase(Country);
    AddMetaField(id);
    AddMetaField(name);
    AddMetaField(alpha2);
    AddMetaField(countryCode);

    // 1+2+3
    _meta.MetaIdMegnevIndex(0,{1},2);

}

bool Country::isValid()
{
    if(id<0) return false;
    if(name.isEmpty()) return false;
    //if(alpha2.isEmpty()) return false;
    if(alpha2.length()!=2) return false;
    if(countryCode<1) return false;
    if(countryCode>1000) return false;
    //if(netPrice<=0) return false; // ha minusz az ár, stornós
    return true;
}

CSV_ImportModel<Country> Country::CSV_Import(const QList<QVarLengthArray<QString>>& records,
                                             const QChar& separator)
{
    CSV_ImportModel<Country> m;

    int L = records.length();

    CSVHelper::RowToField ixln;
    AddRowToField(ixln, name, "name");
    AddRowToField(ixln, alpha2, "alpha-2");
    AddRowToField(ixln, countryCode, "country-code");

    QMap<QString,int> ixs = ixln.Get_RowIndexes(records[0]);

    for(int i = 1;i<L;i++){
        QVarLengthArray<QString> row = records[i];

        QList<MetaValue> metaValues = CSVHelper::CSV_RowToMetaValues(row, ixs);
        Country item = Country::FromMetaValues(metaValues);
        item.id = 0;

        CSV_ImportModel<Country>::Data data(item, row, i, separator);
        m.Add(data);

        // bool valid = item.isValid();
        // if(valid){
        //     m.append(item);
        // } else{
        //     zInfo("invalid row:"+QString::number(i+1)+" row:"+QString::number(i));
        // }
    }

    return m;
}

//


