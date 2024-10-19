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

public:
    SQLHelper::SQLSettings _sql_settings;
    int _autoComplete_millisec = 1500;
    //int _project = 99;

    Settings(const SQLHelper::SQLSettings&a);

    static QString Get_CimCSVFileName();
    static void Set_CimCSVFileName(const QString& v);

    static QString Get_PartnerCSVFileName();
    static void Set_PartnerCSVFileName(const QString& v);

    static QString Get_TetelCSVFileName();
    static void Set_TetelCSVFileName(const QString& v);

private:
    static QString Get_FileName(const QString& key);
    static void Set_FileName(const QString& key, const QString& v);

    static QString Get_Value(const QString& fn, const QString& group, const QString& key);
    static void Set_Value(const QString& fn, const QString& group, const QString& key, const QString& v);
};

#endif // SETTINGS_H
