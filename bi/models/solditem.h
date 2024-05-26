#ifndef SOLDITEM_H
#define SOLDITEM_H

#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>


class SoldItem
{
public:
    SoldItem();

    QString partnerName;
    QString partnerHq;
    QString fullfillment;
    QString accountNr;
    QString productName;
    QString units;
    QString unitPrice;
    QString netPrice;


    static QList<SoldItem> ImportCSV(const QList<QVarLengthArray<QString>>& records);
    static QVariant GetData(const QVarLengthArray<QString>& row, int ix);
    static QVariant GetData(const QVarLengthArray<QString>& row, const QString &columnName, const QMap<QString, int>& ixs);
    bool isValid();
private:
    static int indexOf(const QVarLengthArray<QString>& row, const QString & column_name);
};

#endif // SOLDITEM_H
