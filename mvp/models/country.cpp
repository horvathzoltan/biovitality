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
    if(alpha2.isEmpty()) return false;
    if(countryCode<=0) return false; // ha minusz a darabszám, stornós
    //if(netPrice<=0) return false; // ha minusz az ár, stornós
    return true;
}

QList<Country> Country::CSV_Import(const QList<QVarLengthArray<QString>>& records)
{
    QList<Country> m;
    // 1. rekord fejléc:
    //ID;Cím
    int L = records.length();
    //if(L<3) return {};

    QVarLengthArray<QString> header = records[0];

    nameof::cstring a0 = NAMEOF(Country::name);
    nameof::cstring a1 = NAMEOF(Country::alpha2);
    QString b0(a0.c_str());

    CSVHelper::RowToField ixln;
    ixln.Add("name", "name");
    ixln.Add("alpha2", "alpha-2");
    ixln.Add("countryCode", "country-code");

    QMap<QString,int> ixs = ixln.Get_RowIndexes(header);
    // excel id az excel csv-ben csak sima id-ként szerepel
    //auto a1 = CSVHelper::IndexOfRow(header,"name");
    //ixs.insert("name",);
    //ixs.insert("alpha2",CSVHelper::IndexOfRow(header,"alpha-2"));
    //ixs.insert("countryCode",CSVHelper::IndexOfRow(header,"country-code"));

    QLocale hu(QLocale::Hungarian);

    for(int i = 1;i<L;i++){
        if(i>=3)break;
        QVarLengthArray<QString> row = records[i];

        Country item;
        QList<MetaValue> metaValues = CSVHelper::CSV_RowToMetaValues(row, ixs);
        item = Country::FromMetaValues(metaValues);

        if(item.isValid()){
            m.append(item);
        } else{
            zInfo("invalid row:"+QString::number(i+1)+" row:"+QString::number(i));
        }
    }

    return m;
}

//


