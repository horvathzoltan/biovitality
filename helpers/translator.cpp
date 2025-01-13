#include "translator.h"
#include "helpers/logger.h"
#include "helpers/typehelper.h"

Translator::Translator() {}

void Translator::AddTranslation_(const QString &lcode, const QString &key, const QString &value)
{
    _translations2[lcode][key]=value;
}

QString Translator::Translate(const QString &key)
{
    if(_languageCode.isEmpty()){
        zWarning(QStringLiteral("No language to translate"));
        return key;
    }

    if(!_translations2.contains(_languageCode)){
        zWarning(QStringLiteral("No translations for language: ")+ _languageCode);
        return key;
    }

    QMap<QString, QString> &m = _translations2[_languageCode];

    if(!m.contains(key)){
        zWarning(QStringLiteral("No translation for wordcode: ")+ key);
        return key;
    }

    return _translations2[_languageCode][key];
}

void Translator::Init()
{
    Add_tr("hu", WCodes::AddSoldItem, "Új számla tétel hozzáadása");

    Add_tr("hu", WCodes::SoldItem, "Számla tétel");
    Add_tr("hu", WCodes::SoldItem::id , "ID");
    Add_tr("hu", WCodes::SoldItem::partnerName , "Partner neve");

    Add_tr("hu", WCodes::SoldItem::partnerHq , "Székhelye");
    Add_tr("hu", WCodes::SoldItem::county , "Megye");
    Add_tr("hu", WCodes::SoldItem::fullfillment , "Teljesítés");
    Add_tr("hu", WCodes::SoldItem::accountNr , "Számlaszám");
    Add_tr("hu", WCodes::SoldItem::productName , "Termék megnevezése");

    Add_tr("hu", WCodes::SoldItem::units , "Darab");
    Add_tr("hu", WCodes::SoldItem::unitPrice , "Egységár");
    Add_tr("hu", WCodes::SoldItem::unitCurrency , "Eá. Pénznem");

    Add_tr("hu", WCodes::SoldItem::netPrice , "Nettó ár");
    Add_tr("hu", WCodes::SoldItem::netCurrency , "Nettó pénznem");

    Add_tr("hu", WCodes::SoldItem::excelId , "Excel ID");

    Add_tr("hu", WCodes::AddAddress, "Új cím hozzáadása");

    Add_tr("hu", WCodes::Address, "Cím");
    Add_tr("hu", WCodes::Address::id , "ID");
    Add_tr("hu", WCodes::Address::postalCode , "Irányítószám");
    Add_tr("hu", WCodes::Address::settlementName , "Településnév");
    Add_tr("hu", WCodes::Address::publicAreaName , "Közterületnév");
    Add_tr("hu", WCodes::Address::excelId , "ExcelId ID");
    Add_tr("hu", WCodes::Address::countyId , "Megye");
    Add_tr("hu", WCodes::Address::countryId , "Ország");

    Add_tr("hu", WCodes::Validation::CannotConvert , "Az érték nem konvertálható");
    Add_tr("hu", WCodes::Validation::NoConverterRegisteredFrom , "Nincs regisztrált konverter");



}
