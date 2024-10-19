#ifndef GLOBALS_H
#define GLOBALS_H

#include "mvp/models/solditem.h"
#include "mvp/models/county.h"
#include "mvp/models/address.h"
#include "mvp/models/article.h"
#include "mvp/models/partner.h"


#include "repositories/sqlrepository.h"
#include "settings.h"
#include <QLocale>

#include <helpers/translator.h>


class Helpers{
public:
    SQLHelper _sqlHelper;    
};

class Repositories
{
public:
    Repositories()
        :solditem("SoldItem")
        ,county("County")
        ,article("Article")
        ,address("Address")
        ,partner("Partner"){}

    SqlRepository<SoldItem> solditem;
    SqlRepository<County> county;
    SqlRepository<Article> article;
    SqlRepository<Address> address;
    SqlRepository<Partner> partner;

    static void MetaInit(){
        SoldItem::MetaInit();
        County::MetaInit();
        Article::MetaInit();
        Address::MetaInit();
        Partner::MetaInit();
    }
};

template class SqlRepository<SoldItem>;
template class SqlRepository<County>;
template class SqlRepository<Article>;
template class SqlRepository<Address>;
template class SqlRepository<Partner>;

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
