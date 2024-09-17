#ifndef GLOBALS_H
#define GLOBALS_H

#include "bi/models/solditem.h"
#include "bi/models/county.h"
#include "bi/repositories/sqlrepository.h"
#include "settings.h"
#include <QLocale>

#include <helpers/translator.h>

#include <bi/models/address.h>
#include <bi/models/article.h>

class Helpers{
public:
    SQLHelper _sqlHelper;    
};

class Repositories
{
public:
    Repositories()
        :sr("SoldItem")
        ,cr("County")
        ,ar("Article")
        ,address("Address"){}

    SqlRepository<SoldItem> sr;
    SqlRepository<County> cr;
    SqlRepository<Article> ar;
    SqlRepository<Address> address;

    static void MetaInit(){
        SoldItem::MetaInit();
        County::MetaInit();
        Article::MetaInit();
        Address::MetaInit();
    }
};

template class SqlRepository<SoldItem>;
template class SqlRepository<County>;
template class SqlRepository<Article>;
template class SqlRepository<Address>;

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
    Translator _translator;
public:
    Globals():hu(QLocale::Hungarian){};
};

#endif // GLOBALS_H
