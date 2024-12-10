#include "solditem.h"
#include "helpers/logger.h"

#include <QRegularExpression>
#include <QVarLengthArray>

#include <helpers/stringhelper.h>

#include <meta/csvhelper.h>

Meta<SoldItem> SoldItem::_meta;

SoldItem::SoldItem() {}

void SoldItem::MetaInit()
{
    AddMetaBase(SoldItem);
    AddMetaField(id);
    AddMetaField(partnerName);
    AddMetaField(partnerHq);
    AddMetaField(county);
    AddMetaField(fullfillment);
    AddMetaField(accountNr);
    AddMetaField(productName);
    AddMetaField(units);
    AddMetaField(unitPrice);
    AddMetaField(unitCurrency);
    AddMetaField(netPrice);
    AddMetaField(netCurrency);
    AddMetaField(excelId);
}

bool SoldItem::isValid()
{
    if(id<0) return false;
    if(partnerName.isEmpty()) return false;
    if(partnerHq.isEmpty()) return false;
    //if(units<=0) return false; // ha minusz a darabszám, stornós
    //if(netPrice<=0) return false; // ha minusz az ár, stornós
    return true;
}

/*
ID;Partner neve;Székhelye;Megye;Teljesítés;Számlaszám;Termék megnevezése;Db;Egységár;Eá. Pénznem;Nettó ár;Nettó pénznem
806.;Balmazpharm Kft.;4060 Balmazújváros, Bocskai u. 2-4.;HAJDÚ-BIHAR MEGYE;2020.04.10;2024-100;Probiotikum;40;1 625,00   ;HUF;65 000   ;HUF
807.;Balmazpharm Kft.;4060 Balmazújváros, Bocskai u. 2-4.;HAJDÚ-BIHAR MEGYE;2020.04.10;2024-100;Ginseng;20;870,00   ;HUF;17 400   ;HUF
808.;Balmazpharm Kft.;4060 Balmazújváros, Bocskai u. 2-4.;HAJDÚ-BIHAR MEGYE;2020.04.10;2024-100;Ginseng;13;5,00   ;HUF;65   ;HUF
*/

CSV_ImportModel<SoldItem> SoldItem::CSV_Import(const QList<QVarLengthArray<QString>>& records,
                                               const QChar& separator)
{
    CSV_ImportModel<SoldItem> m;
    // 1. rekord fejléc:
    //Partner neve,Székhelye,Teljesítés,Számlaszám,Termék megnevezése,Db,Egységár,Nettó ár
    int L = records.length();
    if(L<3) return {};

    auto header = records[0];

    QMap<QString,int> ixs;

    QString excelId_KEY(QT_STRINGIFY(id));
    QString partnerName_KEY(QT_STRINGIFY(partnerName));
    QString partnerHq_KEY(QT_STRINGIFY(partnerHq));
    QString county_KEY(QT_STRINGIFY(county));
    QString fullfillment_KEY(QT_STRINGIFY(fullfillment));
    QString accountNr_KEY(QT_STRINGIFY(accountNr));
    QString productName_KEY(QT_STRINGIFY(productName));
    QString units_KEY(QT_STRINGIFY(units));
    QString unitPrice_KEY(QT_STRINGIFY(unitPrice));
    QString unitCurrency_KEY(QT_STRINGIFY(unitCurrency));
    QString netPrice_KEY(QT_STRINGIFY(netPrice));
    QString netCurrency_KEY(QT_STRINGIFY(netCurrency));


    ixs.insert(excelId_KEY,CSVHelper::IndexOfRow(header,"ID"));
    ixs.insert(partnerName_KEY,CSVHelper::IndexOfRow(header,"Partner neve"));
    ixs.insert(partnerHq_KEY,CSVHelper::IndexOfRow(header,"Szekhelye"));
    ixs.insert(county_KEY,CSVHelper::IndexOfRow(header,"Megye"));
    ixs.insert(fullfillment_KEY,CSVHelper::IndexOfRow(header,"Teljesítés"));
    ixs.insert(accountNr_KEY,CSVHelper::IndexOfRow(header,"Számlaszám"));
    ixs.insert(productName_KEY,CSVHelper::IndexOfRow(header,"Termék megnevezése"));
    ixs.insert(units_KEY,CSVHelper::IndexOfRow(header,"Db"));
    ixs.insert(unitPrice_KEY,CSVHelper::IndexOfRow(header,"Egységár"));
    ixs.insert(unitCurrency_KEY,CSVHelper::IndexOfRow(header,"Eá. Pénznem"));
    ixs.insert(netPrice_KEY,CSVHelper::IndexOfRow(header,"Nettó ár"));
    ixs.insert(netCurrency_KEY,CSVHelper::IndexOfRow(header,"Nettó pénznem"));

    QLocale hu(QLocale::Hungarian);

    for(int i = 1;i<L;i++){
        //if(i>=3)break;
        QVarLengthArray<QString> row = records[i];
        SoldItem item;
        QVariant excelIdValue = CSVHelper::GetData(row, excelId_KEY, ixs);

        item.id = 0;
        item.excelId = CSVHelper::GetId(excelIdValue);
        item.partnerName = CSVHelper::GetData(row, partnerName_KEY, ixs).toString();
        item.partnerHq = CSVHelper::GetData(row, partnerHq_KEY, ixs).toString();
        item.county = CSVHelper::GetData(row, county_KEY, ixs).toString();
        //"2020.04.10"
        QVariant d1 = CSVHelper::GetData(row, fullfillment_KEY, ixs);
        item.fullfillment = hu.toDate(d1.toString(),"yyyy.M.d");
        item.accountNr = CSVHelper::GetData(row, accountNr_KEY, ixs).toString();
        item.productName = CSVHelper::GetData(row, productName_KEY, ixs).toString();
        item.units = CSVHelper::GetData(row, units_KEY, ixs).toUInt();


        item.unitPrice = GetPrice2(CSVHelper::GetData(row, unitPrice_KEY, ixs), hu);
        item.unitCurrency = CSVHelper::GetData(row, unitCurrency_KEY, ixs).toString();

        item.netPrice = GetPrice2(CSVHelper::GetData(row, netPrice_KEY, ixs), hu);
        item.netCurrency = CSVHelper::GetData(row, netCurrency_KEY, ixs).toString();


        CSV_ImportModel<SoldItem>::Data data(item, row, i, separator);
        m.Add(data);

        // if(item.isValid()){
        //     m.append(item);
        // } else{
        //     zInfo("invalid row:"+QString::number(i+1)+" excelId:"+excelIdValue.toString());
        // }
    }

    return m;
}

qreal SoldItem::GetPrice2(const QVariant& v, const QLocale& locale){
    QString txt = v.toString().remove(' ');

    bool ok;
    qreal i = locale.toDouble(txt, &ok);
    if(ok) return i;
    return 0;
}

// SoldItem::PriceModel SoldItem::GetPrice(const QVariant& v)
// {
//     QRegularExpression p(R"(([\d\W]*)\s*([a-zA-Z]*))");
//     QRegularExpression space(R"(\W)");
//     QRegularExpressionMatch m = p.match(v.toString());
//     bool hasMatch = m.hasMatch();
//     int lastCapturedIndex= m.lastCapturedIndex();
//     if(hasMatch && lastCapturedIndex>=2){
//         bool ok;
//         qreal a = m.captured(1).remove(space).toDouble(&ok);
//         if(ok) return {.amount=a, .currency=m.captured(2)};
//     }
//     return {};
// }



// void Meta::Init()
// {
//     _isInited = false;

//     _isInited = true;
// }

// int Meta::GetOffset(){
//     SoldItem i[2];
//     char* p0 = (char*)&i[0];
//     char* r0 =  (char*)(&(i[0].id));
//     int o0 = r0-p0;
//     return o0;
// }

// void Meta::AddField(const QString &name, const QMetaType& t, int o)
// {
//     MetaField f;
//     f.name=name;
//     f.type = t;
//     f._offset = o;
//     _fields.append(f);
// }

// QString Meta::GetFieldList()
// {
//     if(!_isInited) return {};
//     QString e;
//     for(auto&a:_fields){
//         if(a.name.toLower()=="id") continue;
//         if(!e.isEmpty()) e+=",";
//         e+=a.name;
//     }
//     return e;
// }


/*SoldItem s = SoldItem::FromSQL(r);
        QSqlField f = records.first().field("partnerName");
        QVariant v = f.value();
        QMetaType targetType = f.metaType();// v.metaType();//QMetaType::fromType<>();


        //s.partnerName = v.value<QString>(); //
        auto b = qvariant_cast<QString>(v);

        QMetaType::convert(v.metaType(), v.constData(), targetType, &s.partnerName);


        zTrace();*/
//}



