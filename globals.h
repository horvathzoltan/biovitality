#ifndef GLOBALS_H
#define GLOBALS_H

#include "bi/models/solditem.h"
#include "bi/repositories/sqlrepository.h"
#include "settings.h"
#include <QLocale>

class Helpers{
public:
    SQLHelper _sqlHelper;
};

class Repositories
{
public:
    Repositories():sr("SoldItem"){}

    SqlRepository<SoldItem> sr;
};

class Globals
{
public:

    Settings _settings{{
                        "QMARIADB",
                         "biovitality",
                         {{"192.168.1.105", 3306}},
                         "zoli",
                         "Aladar123"
        }};

    Helpers _helpers;
    Repositories _repositories;
    QLocale hu;

public:
    Globals():hu(QLocale::Hungarian){};
};

#endif // GLOBALS_H
