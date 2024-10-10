#include "sqlrepository.h"
//#include "bi/models/solditem.h"

#include "globals.h"
#include "helpers/logger.h"
#include <helpers/sqlhelper.h>

#include <QSqlField>
#include <settings.h>

#include <bi/helpers/sqlmetahelper.h>

// template class SqlRepository<SoldItem>;
// template class SqlRepository<County>;
// template class SqlRepository<Article>;
// template class SqlRepository<Address>;

extern Globals _globals;

template<class T>
SqlRepository<T>::SqlRepository(const QString& tname) : SqlExcelRepository(tname), RepositoryBase(tname) {}



const QString RepositoryBase::CONTAINS_CMD =
    QStringLiteral("SELECT EXISTS(SELECT 1 FROM %1 WHERE id = %2) AS _exists;");

const QString RepositoryBase::GET_CMD =
    QStringLiteral("SELECT %1 FROM %2 WHERE id = %3;");

const QString RepositoryBase::GETALL_CMD =
    QStringLiteral("SELECT %2 FROM %1;");

const QString RepositoryBase::UPDATE_CMD =
    QStringLiteral("UPDATE %1 SET %2 WHERE id=:id;");

const QString RepositoryBase::INSERT_CMD =
    QStringLiteral("INSERT INTO %1 (%2) VALUES (%3);");

const QString RepositoryBase::TABLE_EXISTS_CMD =
    QStringLiteral("call sys.table_exists('%1', '%2', @table_type); SELECT @table_type;");

bool RepositoryBase::Contains(int id)
{
    bool exists = false;

    QString cmd = CONTAINS_CMD.arg(tableName()).arg(id);
    zInfo("cmd:"+cmd);
    //QSqlQuery q = _sqlHelper.GetQuery(cmd);
    QList<QSqlRecord> records = _globals._helpers._sqlHelper.DoQuery(cmd);

    if(!records.isEmpty()){
        QVariant a = records.first().value("_exists");
        exists = a.toBool();
    }

    return exists;
}

template<class T>
T SqlRepository<T>::Get(int id)
{
    QString fieldList=T::GetMetaFieldList();

    QString cmd=GET_CMD.arg(fieldList).arg(tableName()).arg(id);
    zInfo("cmd:"+cmd);
    QList<QSqlRecord> records = _globals._helpers._sqlHelper.DoQuery(cmd);

    if(!records.isEmpty())
    {
        QSqlRecord r = records.first();
        QList<MetaValue> m = SqlMetaHelper::RecordToMetaValues(r);
        T s = T::FromMetaValues(m);
        if(s.isValid())
        {
            return s;
        }
    }

    return {};
}

template<class T>
QList<T> SqlRepository<T>::GetAll()
{
    QString fieldList=T::GetMetaFieldList();

    QString cmd=GETALL_CMD.arg(tableName()).arg(fieldList);
    zInfo("cmd:"+cmd);
    //QSqlQuery q = _sqlHelper.GetQuery(cmd);
    QList<QSqlRecord> records = _globals._helpers._sqlHelper.DoQuery(cmd);

    QList<T> items;
    if(!records.isEmpty())
    {
        for(auto&r:records)
        {
            QList<MetaValue> m = SqlMetaHelper::RecordToMetaValues(r);
            T s = T::FromMetaValues(m);
            if(s.isValid())
            {
                items.append(s);
            }
        }
    }
    return items;

}

template<class T>
bool SqlRepository<T>::Update(const T &m)
{
    QList<SQLHelper::SQLParam> params = m.GetQueryParams();
    QString fieldList=SQLHelper::GetFieldList_UPDATE(params);
    QString cmd=UPDATE_CMD.arg(tableName()).arg(fieldList);
    zInfo("cmd:"+cmd);
    QList<QSqlRecord> records = _globals._helpers._sqlHelper.DoQuery(cmd, params);

    return true;
}

template<class T>
bool SqlRepository<T>::Add(const T &m){
    QList<SQLHelper::SQLParam> params = m.GetQueryParams();
    QString fieldList=SQLHelper::GetFieldList_INSERT(params);
    QString paramList=SQLHelper::GetParamList_INSERT(params);

    QString cmd=INSERT_CMD.arg(tableName()).arg(fieldList).arg(paramList);
    zInfo("cmd:"+cmd);
    QList<QSqlRecord> records = _globals._helpers._sqlHelper.DoQuery(cmd, params);

    return true;

}

template<typename T>
bool SqlRepository<T>::isTableExists()
{
    QString dbName = _globals._helpers._sqlHelper.dbName();
    //QString cmd=TABLE_EXISTS_CMD.arg(dbName).arg("Article");//tableName());
    //QString cmd="SELECT COUNT(*) FROM Article;";
    QString cmd="call sys.table_exists('biovitality', 'Article', @table_type);";
    QString cmd1="SELECT @table_type;";
    zInfo("cmd:"+cmd);
    QList<QSqlRecord> records = _globals._helpers._sqlHelper.DoQuery(cmd, {});
    //QList<QSqlRecord> records1 = _globals._helpers._sqlHelper.DoQuery(cmd1, {});


    if(!records.isEmpty())
    {
        auto r = records.first();
        auto rr = r.value(0).toString();
        zInfo("r:"+rr);
    }
    return false;
}


/**/


