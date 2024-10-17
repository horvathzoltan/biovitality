#include "partner.h"

#include <meta/csvhelper.h>

Meta<Partner> Partner::_meta;

Partner::Partner() {}

Partner::Partner(int i, const QString &n, int e)
{
    id = i; Name = n; excelId = e;
}

void Partner::MetaInit()
{
    AddMetaBase(Partner);
    AddMetaField(id); // id
    AddMetaField(Name); //megnev
    AddMetaField(excelId); //excelId

    _meta.MetaIdMegnevIndex(0,1,-1);
    //AddMetaIdMegnevIndex(id, name, KSH_code);
}

bool Partner::isValid()
{
    if(id<0) return false;
    if(Name.isEmpty()) return false;
    return true;
}

QList<Partner> Partner::CSV_Import(const QList<QVarLengthArray<QString>>& records)
{
    QList<Partner> m;
    // 1. rekord fejléc:
    //ID;Cím
    int L = records.length();
    if(L<3) return {};

    auto header = records[0];

    QMap<QString,int> ixs;

    // excel id az excel csv-ben csak sima id-ként szerepel
    QString excelId_KEY("ID");

    //QString postalCode_KEY(QT_STRINGIFY(postalCode));
    QString partnerNev_KEY("Partner megnvezés");
    //QString publicAreaName_KEY(QT_STRINGIFY(publicAreaName));

    ixs.insert(excelId_KEY,CSVHelper::IndexOfRow(header,"ID"));
    ixs.insert(partnerNev_KEY,CSVHelper::IndexOfRow(header,"Partner megnvezés"));

    QLocale hu(QLocale::Hungarian);

    for(int i = 1;i<L;i++){
        //if(i>=3)break;
        QVarLengthArray<QString> row = records[i];
        Partner item;
        QVariant excelIdValue = CSVHelper::GetData(row, excelId_KEY, ixs);

        item.id = 0;
        item.excelId = CSVHelper::GetId(excelIdValue);

        item.Name = CSVHelper::GetData(row, partnerNev_KEY, ixs).toString();

        //item.Parse(d1);

        if(item.isValid()){
            m.append(item);
        } else{
            zInfo("invalid row:"+QString::number(i+1)+" excelId:"+excelIdValue.toString());
        }
    }

    return m;
}
