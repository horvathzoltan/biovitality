#include "solditemrepository.h"
#include "helpers/logger.h"

#include <helpers/sqlhelper.h>

#include <QSqlField>
#include <settings.h>

#include <bi/helpers/sqlmetahelper.h>

extern Settings _settings;
extern SQLHelper _sqlHelper;

SoldItemRepository::SoldItemRepository() {}

const QString RepositoryBase::CONTAINS_CMD =
    QStringLiteral("SELECT EXISTS(SELECT 1 FROM %1 WHERE id = %2) AS _exists;");

const QString RepositoryBase::CONTAINS_EXCEL_ID_CMD =
    QStringLiteral("SELECT EXISTS(SELECT 1 FROM %1 WHERE excelId = %2) AS _exists;");

const QString RepositoryBase::GET_CMD =
    QStringLiteral("SELECT %1 FROM %2 WHERE id = %3;");

const QString RepositoryBase::GETALL_CMD =
    QStringLiteral("SELECT %2 FROM %1;");

const QString RepositoryBase::UPDATE_CMD =
    QStringLiteral("UPDATE %1 SET %2 WHERE id=:id;");

const QString RepositoryBase::INSERT_CMD =
    QStringLiteral("INSERT INTO %1 (%2) VALUES (%3);");

const QString RepositoryBase::TABLE_NAME =
    QStringLiteral("SoldItem");


bool RepositoryBase::Contains(int id)
{
    bool exists = false;

    QString cmd = CONTAINS_CMD.arg(TABLE_NAME).arg(id);
    zInfo("cmd:"+cmd);
    //QSqlQuery q = _sqlHelper.GetQuery(cmd);
    QList<QSqlRecord> records =_sqlHelper.DoQuery(cmd);

    if(!records.isEmpty()){
        QVariant a = records.first().value("_exists");
        exists = a.toBool();
    }

    return exists;
}

bool SoldItemRepository::ContainsBy_ExcelId(int id)
{
    bool exists = false;

    QString cmd = CONTAINS_EXCEL_ID_CMD.arg(TABLE_NAME).arg(id);
    zInfo("cmd:"+cmd);
    //QSqlQuery q = _sqlHelper.GetQuery(cmd);
    QList<QSqlRecord> records =_sqlHelper.DoQuery(cmd);

    if(!records.isEmpty()){
        QVariant a = records.first().value("_exists");

        exists = a.toBool();
    }

    return exists;
}

SoldItem SoldItemRepository::Get(int id)
{
    QString fieldList=SoldItem::GetMetaFieldList();

    QString cmd=GET_CMD.arg(fieldList).arg(TABLE_NAME).arg(id);
    zInfo("cmd:"+cmd);
    //QSqlQuery q = _sqlHelper.GetQuery(cmd);
    QList<QSqlRecord> records = _sqlHelper.DoQuery(cmd);

    if(!records.isEmpty())
    {
        QSqlRecord r = records.first();
        QList<MetaValue> m = SqlMetaHelper::RecordToMetaValues(r);
        SoldItem s = SoldItem::FromMetaValues(m);
        if(s.isValid())
        {
            return s;
        }
    }

    return {};
}

QList<SoldItem> SoldItemRepository::GetAll()
{
    QString fieldList=SoldItem::GetMetaFieldList();

    QString cmd=GETALL_CMD.arg(TABLE_NAME).arg(fieldList);
    zInfo("cmd:"+cmd);
    //QSqlQuery q = _sqlHelper.GetQuery(cmd);
    QList<QSqlRecord> records = _sqlHelper.DoQuery(cmd);

    QList<SoldItem> items;
    if(!records.isEmpty())
    {
        for(auto&r:records)
        {
            QList<MetaValue> m = SqlMetaHelper::RecordToMetaValues(r);
            SoldItem s = SoldItem::FromMetaValues(m);
            if(s.isValid())
            {
                items.append(s);
            }
        }
    }
    return items;

}

// UPDATE SET clients ClientName=:name, ClientCity=:city, ClientAddress=:address, ClientMol=:mol, ClientEik=:eik, ClientVat=:vat, ClientTel=:tel, ClientMail=:mail WHERE ROWID=:rowid
bool SoldItemRepository::Update(const SoldItem &m)
{
    QList<SQLHelper::SQLParam> params = m.GetQueryParams();
    QString fieldList=SQLHelper::GetFieldList_UPDATE(params);
    QString cmd=UPDATE_CMD.arg(TABLE_NAME).arg(fieldList);
    zInfo("cmd:"+cmd);
    QList<QSqlRecord> records = _sqlHelper.DoQuery(cmd, params);

    return true;
}

bool SoldItemRepository::Add(const SoldItem &m){
    QList<SQLHelper::SQLParam> params = m.GetQueryParams();
    QString fieldList=SQLHelper::GetFieldList_INSERT(params);
    QString paramList=SQLHelper::GetParamList_INSERT(params);

    QString cmd=INSERT_CMD.arg(TABLE_NAME).arg(fieldList).arg(paramList);
    zInfo("cmd:"+cmd);
    QList<QSqlRecord> records = _sqlHelper.DoQuery(cmd, params);

    return true;

}
