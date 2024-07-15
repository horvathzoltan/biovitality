#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QMap>


class WCodes{
public:
    class SoldItem{
    public:
        int id;
        int partnerName;
        int partnerHq;
        int county;
        int fullfillment;
        int accountNr;
        int productName;
        int units=-1;
        int unitPrice=0;
        int unitCurrency;
        int netPrice=0;
        int netCurrency;
        int excelId=-1;
    };
};

#define AddTr(a, b, c) AddTr2(a, #b, c,  sizeof(b));



class Translator
{
private:
    QString _languageCode;
    QMap<QString, QString> _translations;
public:
    Translator();

    void AddTranslation(const QString &lcode, const QString& key, const QString& value);

    QString tr(const QString& key);

    void Init();

    void AddTr2(const QString &lcode, const QString& key, const QString& value, unsigned long e){
        AddTranslation(lcode, key, value);
    }
};

#endif // TRANSLATOR_H
