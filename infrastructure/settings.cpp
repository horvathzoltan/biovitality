#include "settings.h"

#include <QSettings>

const QString Settings::FilesIni_FileName = QStringLiteral("files.ini");
const QString Settings::FilesIni_Group = QStringLiteral("files");
const QString Settings::FilesIni_CimCSVFileName = QStringLiteral("addressFile");
const QString Settings::FilesIni_PartnerCSVFileName = QStringLiteral("partnerFile");

const QString Settings::FilesIni_TetelCSVFileName = QStringLiteral("soldItemFile");
const QString Settings::FilesIni_CountryCSVFileName = QStringLiteral("countryFile");
const QString Settings::FilesIni_CountyCSVFileName = QStringLiteral("countyFile");
const QString Settings::FilesIni_ArticleCSVFileName = QStringLiteral("articleFile");

Settings::Settings(const SQLHelper::SQLSettings& a)
{
    this->_sql_settings = a;
}

// address - cim
QString Settings::Get_CSVFileName_Address()
{
    return Get_FileName(FilesIni_CimCSVFileName);
}

void Settings::Set_CSVFileName_Address(const QString &v)
{
    Set_FileName(FilesIni_CimCSVFileName, v);
}

// partner
QString Settings::Get_CSVFileName_Partner()
{
    return Get_FileName(FilesIni_PartnerCSVFileName);
}

void Settings::Set_CSVFileName_Partner(const QString &v)
{
    Set_FileName(FilesIni_PartnerCSVFileName, v);
}

//tetel
QString Settings::Get_CSVFileName_SoldItem()
{
    return Get_FileName(FilesIni_TetelCSVFileName);
}

void Settings::Set_CSVFileName_SoldItem(const QString &v)
{
    Set_FileName(FilesIni_TetelCSVFileName, v);
}

// country - országok
QString Settings::Get_CSVFileName_Country()
{
    return Get_FileName(FilesIni_CountryCSVFileName);
}

void Settings::Set_CSVFileName_Country(const QString &v)
{
    Set_FileName(FilesIni_CountryCSVFileName, v);
}

// county - megyék
QString Settings::Get_CSVFileName_County()
{
    return Get_FileName(FilesIni_CountyCSVFileName);
}

void Settings::Set_CSVFileName_County(const QString &v)
{
    Set_FileName(FilesIni_CountyCSVFileName, v);
}

// cikkek - article
QString Settings::Get_CSVFileName_Article()
{
    return Get_FileName(FilesIni_ArticleCSVFileName);
}

void Settings::Set_CSVFileName_Article(const QString &v)
{
    Set_FileName(FilesIni_ArticleCSVFileName, v);
}

//
QString Settings::Get_FileName(const QString &key)
{
    return Get_Value(FilesIni_FileName, FilesIni_Group, key);
}

void Settings::Set_FileName(const QString& key, const QString &v)
{
   Set_Value(FilesIni_FileName, FilesIni_Group, key, v);
}

//
QString Settings::Get_Value(const QString &fn, const QString &group, const QString &key)
{
    QSettings files(fn, QSettings::IniFormat);
    files.beginGroup(group);
    QString v = files.value(key).toString();
    files.endGroup();
    return v;
}

void Settings::Set_Value(const QString &fn, const QString &group, const QString &key, const QString &v)
{
    QSettings files(fn, QSettings::IniFormat);
    files.beginGroup(group);
    files.setValue(key, v);
    files.endGroup();
}
