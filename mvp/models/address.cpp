#include "address.h"

#include "qregularexpression.h"

#include "meta/csvhelper.h"

#include "mvp/models/county.h"
#include "mvp/models/country.h"

MetaData<Address> Address::_meta;

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
    //AddMetaField(county2Id);
    //AddMetaField(county3Id);

    AddMetaField(countryId);

    // 1+2+3
    //_meta.MetaIdMegnevIndex(0,{1,2,3},-1);

    _meta.SetMetaIdMegnev(Address, id, postalCode);
    _meta.AddMegnev(Address, settlementName);
    _meta.AddMegnev(Address, publicAreaName);

    AddRefs();
}


void Address::AddRefs(){    
    _meta.AddMetaReference_1N(Address, countyId, County, id);
    //_meta.AddMetaReference_1N(Address, county2Id, County, id);
    //_meta.AddMetaReference_1N(Address, county3Id, County, id);

    _meta.AddMetaReference_1N(Address, countryId, Country, id);
}

void Address::DeleteRefs(){
    _meta.DeleteMetaReference(Address, countyId, County);
    //_meta.DeleteMetaReference(Address, county2Id, County);
    //_meta.DeleteMetaReference(Address, county3Id, County);

    _meta.DeleteMetaReference(Address, countryId, Country);
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

    QVarLengthArray<QString> header = records[0];

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
        // vesszük az adatsort
        QVarLengthArray<QString> row = records[i];
        QStringList fieldsWithData;

        Address item;

        item.id = 0;

        // ha volt benne adat,akkor
        bool has_excelIdValue = CSVHelper::HasData(row, excelId_KEY, ixs);
        if(has_excelIdValue){
            // ha van benne adat, akkor a mező nevét felvesszük az adattal rendelkező mezők listájába
            fieldsWithData.append(excelId_KEY);

            QVariant excelIdValue = CSVHelper::GetData(row, excelId_KEY, ixs);
            item.excelId = CSVHelper::GetId(excelIdValue);
        }


        QString d1 = CSVHelper::GetData(row, cim_KEY, ixs).toString();        
        // d1 -> postalCode, settlementName, publicAreaName
        item.ParseAddressFields_private(d1);

        // todo 01aaa1 countyId a településnév alapján valahogyan
        // todo 01aaa2 countryId az országkód a megye alapján?

        // todo 01aaa3 itt nem a csv-ből jövő mezőkből kell a van-e adat benne következtetést levonni,
        // hanem ahogy a parse előállítja az adatot a mezőkbe:
        // d1 -> postalCode, settlementName, publicAreaName
        // ahoz hasonlóan kell az információ arról, hogy jött-e adat az adott mezőbe
        // hiszen a cím string is fel van dolgozva és szétesik elemekre
        // itt már releváns az, hogy jött-e adat az adott elembe



        // todo 02 d1-be kellenek a mezők amik bejöttek a csv-ből
        // ezek a headerben vannak
        // kell egy HasData függfény, ami felsorolja azokat a merőket, amiken valamiféle adat van

        CSV_ImportModel<Address>::Data data(item, row, i, separator, fieldsWithData);
        m.Add(data);
        // if(item.isValid()){
        //     m.append(item);
        // } else{
        //     zInfo("invalid row: "+QString::number(i+1)+" excelId: "+excelIdValue.toString());
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


