#include "address.h"

#include "qregularexpression.h"

#include <meta/csvhelper.h>

Meta<Address> Address::_meta;

Address::Address() {}

void Address::MetaInit()
{
    AddMetaBase(Address);
    AddMetaField(id);
    AddMetaField(postalCode);
    AddMetaField(settlementName);
    AddMetaField(publicAreaName);
    AddMetaField(excelId);

    AddMetaField(countyId);
    AddMetaField(countryId);
    // 1+2+3
    _meta.MetaIdMegnevIndex(0,{1,2,3},-1);

    //ref1;
    //_meta.AddMetaRef<County>("countyId","County", "id");
    //_meta.AddMetaRef<Country>("countryId","Country", "id");
    //countyRef;
    AddRefs();
}

void Address::AddRefs(){
    _meta.AddMetaRef<County>("countyId","County", "id");
    _meta.AddMetaRef<Country>("countryId","Country", "id");
}

void Address::DeleteRefs(){
    _meta.DeleteMetaRef<County>();
    _meta.DeleteMetaRef<Country>();
}


bool Address::isValid()
{
    if(id<0) return false;
    if(settlementName.isEmpty()) return false;
    if(publicAreaName.isEmpty()) return false;
    //if(units<=0) return false; // ha minusz a darabszám, stornós
    //if(netPrice<=0) return false; // ha minusz az ár, stornós
    return true;
}
/*
ID;Cím
1;4030 Debrecen,  Vágóhíd út 4.b.
2;8394 Alsópáhok, Fő utca 76. B.ép.fszt.5.
*/
CSV_ImportModel<Address> Address::CSV_Import(const QList<QVarLengthArray<QString>>& records,
                                             const QChar& separator)
{
    CSV_ImportModel<Address> m;
    // 1. rekord fejléc:
    //ID;Cím
    int L = records.length();
    if(L<3) return {};

    auto header = records[0];

    QMap<QString,int> ixs;

    // excel id az excel csv-ben csak sima id-ként szerepel
    QString excelId_KEY("ID");

    //QString postalCode_KEY(QT_STRINGIFY(postalCode));
    QString cim_KEY("Cím");
    //QString publicAreaName_KEY(QT_STRINGIFY(publicAreaName));

    ixs.insert(excelId_KEY,CSVHelper::IndexOfRow(header,"ID"));
    ixs.insert(cim_KEY,CSVHelper::IndexOfRow(header,"Cím"));

    QLocale hu(QLocale::Hungarian);

    for(int i = 1;i<L;i++){
        //if(i>=3)break;
        QVarLengthArray<QString> row = records[i];
        Address item;
        QVariant excelIdValue = CSVHelper::GetData(row, excelId_KEY, ixs);

        item.id = 0;
        item.excelId = CSVHelper::GetId(excelIdValue);

        QString d1 = CSVHelper::GetData(row, cim_KEY, ixs).toString();

        item.ParseAddressFields_private(d1);

        CSV_ImportModel<Address>::Data data(item, row, i, separator);
        m.Add(data);
        // if(item.isValid()){
        //     m.append(item);
        // } else{
        //     zInfo("invalid row:"+QString::number(i+1)+" excelId:"+excelIdValue.toString());
        // }
    }

    return m;
}

void Address::ParseAddressFields_private(const QString &c)
{
    if(c.isEmpty()) return;

    static QRegularExpression r(QStringLiteral(R"((\d+)\s*(\w+)\s*,?\s*([\w\W]+))"), QRegularExpression::UseUnicodePropertiesOption	);

    QRegularExpressionMatch m = r.match(c);
    if(m.hasMatch()){
        auto L = m.lastCapturedIndex();
        if(L==3){
            bool ok;
            int i = m.captured(1).toInt(&ok);
            if(ok) postalCode = i;

            settlementName= m.captured(2);
            publicAreaName= m.captured(3);
        }
    }
}


