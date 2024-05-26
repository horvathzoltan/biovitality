#ifndef SOLDITEM_H
#define SOLDITEM_H

#include <QDateTime>
#include <QList>
#include <QVariant>

#include <helpers/filehelper.h>


class SoldItem
{
public:
    SoldItem();

    QString partnerName;
    QString partnerHq;
    QDateTime fullfillment;
    QString accountNr;
    QString productName;
    int units=-1;
    qreal unitPrice=0;
    qreal netPrice=0;
    QString currency;

    struct PriceModel{
        qreal amount=0;
        QString currency="";
    };

    static QList<SoldItem> ImportCSV(const QList<QVarLengthArray<QString>>& records);
    static QVariant GetData(const QVarLengthArray<QString>& row, int ix);
    static QVariant GetData(const QVarLengthArray<QString>& row, const QString &columnName, const QMap<QString, int>& ixs);
    bool isValid();
    static PriceModel GetPrice(const QVariant v);
private:
    static int indexOf(const QVarLengthArray<QString>& row, const QString & column_name);
};

#endif // SOLDITEM_H
