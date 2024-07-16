#include "translator.h"

Translator::Translator() {}

void Translator::AddTranslation(const QString &lcode, const QString &key, const QString &value)
{
    _translations[key]=value;
}

QString Translator::Translate(const QString &key){
    bool c = _translations.contains(key);
    if(!c) return key;
    return _translations.value(key);
}

void Translator::Init()
{
    AddTr("hu", WCodes::AddSoldItem, "Új számla tétel hozzáadása");

    AddTr("hu", WCodes::SoldItem, "Számla tétel");
    AddTr("hu", WCodes::SoldItem::id , "ID");
    AddTr("hu", WCodes::SoldItem::partnerName , "Partner neve");

    AddTr("hu", WCodes::SoldItem::partnerHq , "Székhelye");
    AddTr("hu", WCodes::SoldItem::county , "Megye");
    AddTr("hu", WCodes::SoldItem::fullfillment , "Teljesítés");
    AddTr("hu", WCodes::SoldItem::accountNr , "Számlaszám");
    AddTr("hu", WCodes::SoldItem::productName , "Termék megnevezése");

    AddTr("hu", WCodes::SoldItem::units , "Darab");
    AddTr("hu", WCodes::SoldItem::unitPrice , "Egységár");
    AddTr("hu", WCodes::SoldItem::unitCurrency , "Eá. Pénznem");

    AddTr("hu", WCodes::SoldItem::netPrice , "Nettó ár");
    AddTr("hu", WCodes::SoldItem::netCurrency , "Nettó pénznem");

    AddTr("hu", WCodes::SoldItem::excelId , "Excel ID");
}
