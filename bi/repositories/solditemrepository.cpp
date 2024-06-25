#include "solditemrepository.h"
#include "helpers/logger.h"

#include <helpers/sqlhelper.h>

#include <QSqlField>
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

const QString RepositoryBase::CONTAINS_EXCEL_ID_CMD =
    QStringLiteral("SELECT EXISTS(SELECT 1 FROM %1 WHERE excelId = %2) AS _exists;");

const QString RepositoryBase::GET_CMD =
    QStringLiteral("SELECT %3 FROM %1 WHERE id = %2;");

const QString RepositoryBase::TABLE_NAME =
    QStringLiteral("SoldItem");


bool RepositoryBase::Contains(int id)
{
    bool exists = false;

    QList<QSqlRecord> records =
        _sqlHelper.DoQuery(CONTAINS_CMD.arg(TABLE_NAME).arg(id));

    if(!records.isEmpty()){
        QVariant a = records.first().value("_exists");

        exists = a.toBool();
    }

    return exists;
}

bool SoldItemRepository::ContainsBy_ExcelId(int id)
{
    bool exists = false;

    QList<QSqlRecord> records =
        _sqlHelper.DoQuery(CONTAINS_EXCEL_ID_CMD.arg(TABLE_NAME).arg(id));

    if(!records.isEmpty()){
        QVariant a = records.first().value("_exists");

        exists = a.toBool();
    }

    return exists;
}

SoldItem SoldItemRepository::Get(int id)
{
    QString fieldList=SoldItem::GetMetaFieldList();

    QString cmd=GET_CMD.arg(TABLE_NAME).arg(id).arg(fieldList);
    zInfo("cmd:"+cmd);
     QList<QSqlRecord> records =
         _sqlHelper.DoQuery(cmd);

    SoldItem s;

    if(!records.isEmpty()){
        QSqlField f = records.first().field("partnerName");
        QVariant v = f.value();
        QMetaType targetType = f.metaType();// v.metaType();//QMetaType::fromType<>();

        //s.partnerName = v.value<QString>(); //
        auto b = qvariant_cast<QString>(v);

        QMetaType::convert(v.metaType(), v.constData(), targetType, &s.partnerName);


        zTrace();
    }

    return s;
}
