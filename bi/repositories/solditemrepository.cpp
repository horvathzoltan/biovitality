#include "solditemrepository.h"

#include <helpers/sqlhelper.h>

#include <settings.h>

extern Settings _settings;
extern SQLHelper _sqlHelper;

SoldItemRepository::SoldItemRepository() {}

// void SoldItemRepository::InsertOrUpdate(const QList<SoldItem> &items)
// {
//     for(auto&a:items){
//         // if(a.Exists()){

//         // }
//     }
// }

const QString RepositoryBase::CONTAINS_CMD =
    QStringLiteral("SELECT EXISTS(SELECT 1 FROM %1 WHERE id = %2) AS _exists;");

const QString RepositoryBase::TABLE_NAME =
    QStringLiteral("SoldItem");


bool RepositoryBase::Contains(int id)
{
    bool exists = false;
    //SQLHelper sqlh;
    //sqlh.SetSettings(_settings._sql_settings);

    QList<QSqlRecord> records =
        _sqlHelper.DoQuery(CONTAINS_CMD.arg(TABLE_NAME).arg(id));

    if(!records.isEmpty()){
        QVariant a = records.first().value("_exists");

        exists = a.toBool();
    }

    return exists;
}
