#ifndef TRANSLATOR_H
#define TRANSLATOR_H

#include <QMap>
//#include <typeindex>

namespace _WC_
{
class WCodes{
public:
    void* AddSoldItem;
    void* AddAddress;
    class SoldItem{
    public:
        void* id;
        void* partnerName;
        void* partnerHq;
        void* county;
        void* fullfillment;
        void* accountNr;
        void* productName;
        void* units;
        void* unitPrice;
        void* unitCurrency;
        void* netPrice;
        void* netCurrency;
        void* excelId;
    };
    class Validation{
    public:
        void* CannotConvert;
        void* NoConverterRegisteredFrom;
    };

    class Address{
    public:
        void* id;
        void* postalCode;
        void* settlementName;
        void* publicAreaName;
        void* excelId;
        void* countyId;
        void* countryId;
    };
};
}

#define GetWCode(b) TypeHelper::GetTypeName_(QStringLiteral(#b), sizeof(_WC_::b))
#define Add_tr(a, b, c) AddTranslation_(a, GetWCode(b), c)
#define _tr(b) _globals._translator.Translate(GetWCode(b))

class Translator
{
private:
    QString _languageCode;    
    QMap<QString, QMap<QString, QString>> _translations2;

public:
    Translator();
    void Init();

    void SetLanguageCode(const QString&v){ _languageCode = v;}

    void AddTranslation_(const QString &lcode, const QString& key, const QString& value);
    QString Translate(const QString& key);    
};

#endif // TRANSLATOR_H

