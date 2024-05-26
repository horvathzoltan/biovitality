#include "solditem.h"

#include <QVarLengthArray>

#include <helpers/stringhelper.h>

SoldItem::SoldItem() {}

QList<SoldItem> SoldItem::ImportCSV(const QList<QVarLengthArray<QString>>& records)
{
    QList<SoldItem> m;
    // 1. rekord fejléc:
    //Partner neve,Székhelye,Teljesítés,Számlaszám,Termék megnevezése,Db,Egységár,Nettó ár
    int L = records.length();
    if(L<3) return {};

    auto header = records[0];

    QMap<QString,int> ixs;

    QString partnerName_KEY(QT_STRINGIFY(partnerName));
    QString partnerHq_KEY(QT_STRINGIFY(partnerHq));
    QString fullfillment_KEY(QT_STRINGIFY(fullfillment));
    QString accountNr_KEY(QT_STRINGIFY(accountNr));
    QString productName_KEY(QT_STRINGIFY(productName));
    QString units_KEY(QT_STRINGIFY(units));
    QString unitPrice_KEY(QT_STRINGIFY(unitPrice));
    QString netPrice_KEY(QT_STRINGIFY(netPrice));

    ixs.insert(partnerName_KEY,indexOf(header,"Partner neve"));
    ixs.insert(partnerHq_KEY,indexOf(header,"Szekhelye"));
    ixs.insert(fullfillment_KEY,indexOf(header,"Teljesítés"));
    ixs.insert(accountNr_KEY,indexOf(header,"Számlaszám"));
    ixs.insert(productName_KEY,indexOf(header,"Termék megnevezése"));
    ixs.insert(units_KEY,indexOf(header,"Db"));
    ixs.insert(unitPrice_KEY,indexOf(header,"Egységár"));
    ixs.insert(netPrice_KEY,indexOf(header,"Nettó ár"));

    for(int i = 1;i<L;i++){
        QVarLengthArray<QString> row = records[i];
        SoldItem item;
        item.partnerName = GetData(row, partnerName_KEY, ixs).toString();
        item.partnerHq = GetData(row, partnerHq_KEY, ixs).toString();
        item.fullfillment = GetData(row, fullfillment_KEY, ixs).toString();
        item.accountNr = GetData(row, accountNr_KEY, ixs).toString();
        item.productName = GetData(row, productName_KEY, ixs).toString();
        item.units = GetData(row, units_KEY, ixs).toString();
        item.unitPrice = GetData(row, unitPrice_KEY, ixs).toString();
        item.netPrice = GetData(row, netPrice_KEY, ixs).toString();

        if(item.isValid()){
            m.append(item);
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
    if(partnerName.isEmpty()) return false;
    if(partnerHq.isEmpty()) return false;
    if(units.isEmpty()) return false;
    if(netPrice.isEmpty()) return false;
    return true;
}

QVariant SoldItem::GetData(const QVarLengthArray<QString> &row, int ix){
     if(ix<0) return {};
     if(ix>=row.length()) return {};

     return QVariant(row[ix]);
}
