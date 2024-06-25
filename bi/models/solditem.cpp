#include "solditem.h"
#include "helpers/logger.h"

#include <QRegularExpression>
#include <QVarLengthArray>

#include <helpers/stringhelper.h>

Meta<SoldItem> SoldItem::_meta;

SoldItem::SoldItem() {}

void SoldItem::MetaInit()
{
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
}

/*
ID;Partner neve;Székhelye;Megye;Teljesítés;Számlaszám;Termék megnevezése;Db;Egységár;Eá. Pénznem;Nettó ár;Nettó pénznem
806.;Balmazpharm Kft.;4060 Balmazújváros, Bocskai u. 2-4.;HAJDÚ-BIHAR MEGYE;2020.04.10;2024-100;Probiotikum;40;1 625,00   ;HUF;65 000   ;HUF
807.;Balmazpharm Kft.;4060 Balmazújváros, Bocskai u. 2-4.;HAJDÚ-BIHAR MEGYE;2020.04.10;2024-100;Ginseng;20;870,00   ;HUF;17 400   ;HUF
808.;Balmazpharm Kft.;4060 Balmazújváros, Bocskai u. 2-4.;HAJDÚ-BIHAR MEGYE;2020.04.10;2024-100;Ginseng;13;5,00   ;HUF;65   ;HUF
*/

QList<SoldItem> SoldItem::ImportCSV(const QList<QVarLengthArray<QString>>& records)
{
    QList<SoldItem> m;
    // 1. rekord fejléc:
    //Partner neve,Székhelye,Teljesítés,Számlaszám,Termék megnevezése,Db,Egységár,Nettó ár
    int L = records.length();
    if(L<3) return {};

    auto header = records[0];

    QMap<QString,int> ixs;

    QString ID_KEY(QT_STRINGIFY(id));
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

    ixs.insert(ID_KEY,indexOf(header,"ID"));
    ixs.insert(partnerName_KEY,indexOf(header,"Partner neve"));
    ixs.insert(partnerHq_KEY,indexOf(header,"Szekhelye"));
    ixs.insert(county_KEY,indexOf(header,"Megye"));
    ixs.insert(fullfillment_KEY,indexOf(header,"Teljesítés"));
    ixs.insert(accountNr_KEY,indexOf(header,"Számlaszám"));
    ixs.insert(productName_KEY,indexOf(header,"Termék megnevezése"));
    ixs.insert(units_KEY,indexOf(header,"Db"));
    ixs.insert(unitPrice_KEY,indexOf(header,"Egységár"));
    ixs.insert(unitCurrency_KEY,indexOf(header,"Eá. Pénznem"));
    ixs.insert(netPrice_KEY,indexOf(header,"Nettó ár"));
    ixs.insert(netCurrency_KEY,indexOf(header,"Nettó pénznem"));

    QLocale hu(QLocale::Hungarian);

    for(int i = 1;i<L;i++){
        QVarLengthArray<QString> row = records[i];
        SoldItem item;
        QVariant idValue = GetData(row, ID_KEY, ixs);

        item.id = GetId(idValue);
        item.partnerName = GetData(row, partnerName_KEY, ixs).toString();
        item.partnerHq = GetData(row, partnerHq_KEY, ixs).toString();
        item.county = GetData(row, county_KEY, ixs).toString();

        item.fullfillment = hu.toDate(GetData(row, fullfillment_KEY, ixs).toString());
        item.accountNr = GetData(row, accountNr_KEY, ixs).toString();
        item.productName = GetData(row, productName_KEY, ixs).toString();
        item.units = GetData(row, units_KEY, ixs).toUInt();


        item.unitPrice = GetPrice2(GetData(row, unitPrice_KEY, ixs), hu);
        item.unitCurrency = GetData(row, unitCurrency_KEY, ixs).toString();

        item.netPrice = GetPrice2(GetData(row, netPrice_KEY, ixs), hu);
        item.netCurrency = GetData(row, netCurrency_KEY, ixs).toString();


        if(item.isValid()){
            m.append(item);
        } else{
            zInfo("invalid row:"+QString::number(i+1)+" id:"+idValue.toString());
        }
    }

    return m;
}

int SoldItem::indexOf(const QVarLengthArray<QString>& row, const QString &column_name)
{
    int L = row.length();
    for (int i = 0;i<L;i++) {
        QString a =row[i];
        QString a2 = StringHelper::Normalize(a);
        QString column_name2 = StringHelper::Normalize(column_name);
        if (a2 == column_name2) return i;
    }
    return -1;
}

QVariant SoldItem::GetData(const QVarLengthArray<QString>& row, const QString& columnName, const QMap<QString,int>& ixs){
    if(ixs.contains(columnName)){
        int ix = ixs.value(columnName);
        return GetData(row, ix);
    }
    return {};
}

bool SoldItem::isValid()
{
    if(id<=0) return false;
    if(partnerName.isEmpty()) return false;
    if(partnerHq.isEmpty()) return false;
    //if(units<=0) return false; // ha minusz a darabszám, stornós
    //if(netPrice<=0) return false; // ha minusz az ár, stornós
    return true;
}

int SoldItem::GetId(const QVariant& v){
    QString txt = v.toString();
    if(txt.endsWith('.')) txt = txt.left(txt.length()-1);
    bool ok;
    int i = txt.toInt(&ok);
    if(ok) return i;
    return -1;
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

QVariant SoldItem::GetData(const QVarLengthArray<QString> &row, int ix){
     if(ix<0) return {};
     if(ix>=row.length()) return {};

     return QVariant(row[ix]);
}


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
