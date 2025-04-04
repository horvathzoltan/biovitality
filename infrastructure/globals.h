#ifndef GLOBALS_H
#define GLOBALS_H

#include "mvp/models/solditem.h"
#include "mvp/models/county.h"

#include "mvp/models/address.h"
#include "mvp/models/article.h"
#include "mvp/models/partner.h"
#include "mvp/models/country.h"

#include "repositories/sqlrepository.h"
#include "settings.h"
#include <QLocale>

#include "helpers/optionalconverters.h"
#include "helpers/sysinfohelper.h"
#include "helpers/tcpclient.h"
#include "helpers/translator.h"


class Helpers{
public:
    SQLHelper _sqlHelper;
    SysInfoHelper _sysinfoHelper;
};

class Repositories
{
public:
    Repositories()
        :solditem("SoldItem")
        ,county("County")
        ,article("Article")
        ,address("Address")
        ,partner("Partner")
        ,country("Country"){

        // _repos.append(&solditem);
        // _repos.append(&county);
        // _repos.append(&solditem);
        // _repos.append(&solditem);
        // _repos.append(&solditem);
        // _repos.append(&solditem);
    }

    //QList<RepositoryBase*> _repos;

    SqlRepository<SoldItem> solditem;
    SqlRepository<County> county;
    SqlRepository<Article> article;
    SqlRepository<Address> address;
    SqlRepository<Partner> partner;
    SqlRepository<Country> country;        

    static void MetaInit(){
        SoldItem::Meta().SetVerbose(false);
        Article::Meta().SetVerbose(false);
        County::Meta().SetVerbose(false);
        Address::Meta().SetVerbose(false);

        Country::MetaInit();
        County::MetaInit();
        Article::MetaInit();
        Address::MetaInit();
        Partner::MetaInit();

        SoldItem::MetaInit();
    }            
};


template class SqlRepository<SoldItem>;
template class SqlRepository<County>;
template class SqlRepository<Article>;
template class SqlRepository<Address>;
template class SqlRepository<Partner>;
template class SqlRepository<Country>;

class Globals
{
public:
    Settings _settings;
    // {
    //     {
    //         "QMARIADB",
    //         "biovitality",
    //         {
    //             {"192.168.1.105", 3306},
    //             {"172.16.1.63", 3306}
    //         },
    //         "zoli",
    //         "Aladar123"
    //     }
    // };

    Helpers _helpers;
    Repositories _repositories;
    QLocale hu;
    Translator _translator;
    OptionalConverters _optionalConverter;
    TcpClient _tcpClient;
public:
    Globals():hu(QLocale::Hungarian)
    {
        _optionalConverter.RegisterAll();
    };
};

#endif // GLOBALS_H
