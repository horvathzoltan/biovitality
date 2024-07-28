#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QMap>


class WCodes{
public:
    class AddSoldItem{};
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
    class Validation{
    public:
        int CannotConvert;
    };
};

#define AddTr(a, b, c) AddTr2(a, #b, c,  sizeof(b));
#define GetWCode(b) _globals._translator.GetWCode2(QStringLiteral(#b), sizeof(b))
#define _tr(b) _globals._translator.Translate(b);

class Translator
{
private:
    QString _languageCode;
    QMap<QString, QString> _translations;
public:
    Translator();

    void AddTranslation(const QString &lcode, const QString& key, const QString& value);

    QString tr(const QString& key){ return Translate(key);}
    QString Translate(const QString& key);

    void Init();

    void AddTr2(const QString &lcode, const QString& key, const QString& value, unsigned long l){
        Q_UNUSED(l)
        AddTranslation(lcode, key, value);
    }

    QString GetWCode2(const QString& key, unsigned long l){
        Q_UNUSED(l)
        return key;
    }

    QString Translate2(const QString& key, unsigned long l){
        Q_UNUSED(l)
        return Translate(key);
    }

};

#endif // TRANSLATOR_H

