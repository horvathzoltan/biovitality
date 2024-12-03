#ifndef SETTINGS_H
#define SETTINGS_H
#include <QString>
#include "helpers/sqlhelper.h"

class Settings
{
private:
    static const QString FilesIni_FileName;
    static const QString FilesIni_Group;
    static const QString FilesIni_CimCSVFileName;
    static const QString FilesIni_TetelCSVFileName;
    static const QString FilesIni_PartnerCSVFileName;
    static const QString FilesIni_CountryCSVFileName;
    static const QString FilesIni_CountyCSVFileName;
    static const QString FilesIni_ArticleCSVFileName;

public:
    SQLHelper::SQLSettings _sql_settings;
    int _autoComplete_millisec = 1500;
    //int _project = 99;

    Settings();
    void SetSqlSettings(const SQLHelper::SQLSettings&a);

    static QString Get_CSVFileName_Address();
    static void Set_CSVFileName_Address(const QString& v);

    static QString Get_CSVFileName_Partner();
    static void Set_CSVFileName_Partner(const QString& v);

    static QString Get_CSVFileName_SoldItem();
    static void Set_CSVFileName_SoldItem(const QString& v);

    static QString Get_CSVFileName_Country();
    static void Set_CSVFileName_Country(const QString& v);

    static QString Get_CSVFileName_County();
    static void Set_CSVFileName_County(const QString& v);

    static QString Get_CSVFileName_Article();
    static void Set_CSVFileName_Article(const QString& v);

private:
    static QString Get_FileName(const QString& key);
    static void Set_FileName(const QString& key, const QString& v);

    static QString Get_Value(const QString& fn, const QString& group, const QString& key);
    static void Set_Value(const QString& fn, const QString& group, const QString& key, const QString& v);
};

#endif // SETTINGS_H
