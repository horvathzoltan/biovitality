#ifndef INVOICEHEAD_H
#define INVOICEHEAD_H

#include <QString>
#include <QDate>

class BusinessRecord
{
public:
    BusinessRecord();

    int id=-1;
    QString name;
    QString recordNr;
    QString issuingPartnerId;
    QString orderingPartnerId;
    QDate issuingDate;
    QString description;
    QDate recordingDate;
};

class InvoiceHead : public BusinessRecord
{
public:
    InvoiceHead();

    int id=-1;
    QString partnerName; //partners
    QString partnerHq; //address
    QString county; // county
    QDate fullfillment;
    QString accountNr;
    QString productName; //article
    int units=-1;
    qreal unitPrice=0;
    QString unitCurrency;
    qreal netPrice=0;
    QString netCurrency;
    int excelId=-1;
};

#endif // INVOICEHEAD_H

