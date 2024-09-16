#include "address.h"
#include "qregularexpression.h"

#include <bi/helpers/csvhelper.h>

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
QList<Address> Address::CSV_Import(const QList<QVarLengthArray<QString>>& records)
{
    QList<Address> m;
    // 1. rekord fejléc:
    //ID;Cím
    int L = records.length();
    if(L<3) return {};

    auto header = records[0];

    QMap<QString,int> ixs;

    // excel id az excel csv-ben csak sima id-ként szerepel
    QString excelId_KEY(QT_STRINGIFY(id));

    //QString postalCode_KEY(QT_STRINGIFY(postalCode));
    QString cim_KEY("Cim");
    //QString publicAreaName_KEY(QT_STRINGIFY(publicAreaName));

    ixs.insert(excelId_KEY,CSVHelper::IndexOfRow(header,"ID"));
    ixs.insert(cim_KEY,CSVHelper::IndexOfRow(header,"Cim"));

    QLocale hu(QLocale::Hungarian);

    for(int i = 1;i<L;i++){
        //if(i>=3)break;
        QVarLengthArray<QString> row = records[i];
        Address item;
        QVariant excelIdValue = CSVHelper::GetData(row, excelId_KEY, ixs);

        item.id = 0;
        item.excelId = CSVHelper::GetId(excelIdValue);

        QVariant d1 = CSVHelper::GetData(row, cim_KEY, ixs);

        item.Parse(d1.toString());

        if(item.isValid()){
            m.append(item);
        } else{
            zInfo("invalid row:"+QString::number(i+1)+" excelId:"+excelIdValue.toString());
        }
    }

    return m;
}

void Address::Parse(const QString &c)
{
    if(c.isEmpty()) return;

    static QRegularExpression r(QStringLiteral(R"((\d+)\s*(\w+)\s*,?\s*([\w\W]+))"));
    QRegularExpressionMatch m = r.match(c);
    if(m.hasMatch()){
        if(m.capturedLength()==3){
            bool ok;
            int i = m.captured(1).toInt(&ok);
            if(ok) postalCode = i;

            settlementName= m.captured(2);
            publicAreaName= m.captured(3);
        }
    }
}


