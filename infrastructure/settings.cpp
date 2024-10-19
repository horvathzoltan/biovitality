#include "settings.h"

#include <QSettings>

const QString Settings::FilesIni_FileName = QStringLiteral("files.ini");
const QString Settings::FilesIni_Group = QStringLiteral("files");
const QString Settings::FilesIni_CimCSVFileName = QStringLiteral("addressFile");
const QString Settings::FilesIni_PartnerCSVFileName = QStringLiteral("partnerFile");

const QString Settings::FilesIni_TetelCSVFileName = QStringLiteral("soldItemFile");

Settings::Settings(const SQLHelper::SQLSettings& a)
{
    this->_sql_settings = a;
}

// cim
QString Settings::Get_CimCSVFileName()
{
    return Get_FileName(FilesIni_CimCSVFileName);
}

void Settings::Set_CimCSVFileName(const QString &v)
{
    Set_FileName(FilesIni_CimCSVFileName, v);
}

// partner
QString Settings::Get_PartnerCSVFileName()
{
    return Get_FileName(FilesIni_PartnerCSVFileName);
}

void Settings::Set_PartnerCSVFileName(const QString &v)
{
    Set_FileName(FilesIni_PartnerCSVFileName, v);
}

//tetel
QString Settings::Get_TetelCSVFileName()
{
    return Get_FileName(FilesIni_TetelCSVFileName);
}

void Settings::Set_TetelCSVFileName(const QString &v)
{
    Set_FileName(FilesIni_TetelCSVFileName, v);
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
