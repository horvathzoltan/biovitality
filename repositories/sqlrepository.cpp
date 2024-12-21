#include "sqlrepository.h"
//#include "bi/models/solditem.h"

#include "infrastructure/globals.h"
#include "helpers/logger.h"
#include <helpers/sqlhelper.h>

#include <QSqlField>
#include <infrastructure/settings.h>

#include <meta/sqlmetahelper.h>

// template class SqlRepository<SoldItem>;
// template class SqlRepository<County>;
// template class SqlRepository<Article>;
// template class SqlRepository<Address>;

extern Globals _globals;

//template<class T>
//SqlRepository<T>::SqlRepository(const QString& tname) : SqlExcelRepository(tname), RepositoryBase(tname) {}
//SqlRepository<T>::SqlRepository(const QString& tname) : RepositoryBase(tname) {}

QList<RepositoryBase*> RepositoryBase::_repos;


const QString RepositoryBase::CONTAINS_CMD =
    QStringLiteral("SELECT EXISTS(SELECT 1 FROM %1 WHERE id = %2) AS _exists;");

const QString RepositoryBase::CONTAINS_BY_COLUMN_CMD =
    QStringLiteral("SELECT EXISTS(SELECT 1 FROM %1 WHERE %2 = %3) AS _exists;");

const QString RepositoryBase::GET_ID_BY_COLUMN_CMD =
    QStringLiteral("SELECT id FROM %1 WHERE %2 = %3;");

const QString RepositoryBase::GET_CMD =
    QStringLiteral("SELECT %1 FROM %2 WHERE id = %3;");

const QString RepositoryBase::GETALL_CMD =
    QStringLiteral("SELECT %2 FROM %1;");

const QString RepositoryBase::UPDATE_CMD =
    QStringLiteral("UPDATE %1 SET %2 WHERE id=:id;");

const QString RepositoryBase::INSERT_CMD =
    QStringLiteral("INSERT INTO %1 (%2) VALUES (%3);");

const QString RepositoryBase::TABLE_EXISTS_CMD =
    QStringLiteral("sys.table_exists('%1', '%2', @table_type);");

const QString RepositoryBase::FIELDS_EXISTS_CMD =
    QStringLiteral("SHOW COLUMNS FROM %1 FROM %2;");

bool RepositoryBase::Contains(int id)
{
    bool exists = false;

    QString cmd = CONTAINS_CMD.arg(tableName()).arg(id);
    //zInfo("cmd:"+cmd);
    //QSqlQuery q = _sqlHelper.GetQuery(cmd);
    SQLHelper::DoQueryRModel rm = _globals._helpers._sqlHelper.DoQuery(cmd);

    if(rm.hasRecords()){
        QVariant a = rm.records.first().value("_exists");
        exists = a.toBool();
    }

    return exists;
}

template<class T>
T SqlRepository<T>::Get(int id)
{
    QString fieldNames=T::GetMetaFieldNames();

    QString cmd=GET_CMD.arg(fieldNames).arg(tableName()).arg(id);
    //zInfo("cmd:"+cmd);
    SQLHelper::DoQueryRModel rm = _globals._helpers._sqlHelper.DoQuery(cmd);

    if(rm.hasRecords())
    {
        QSqlRecord r = rm.records.first();
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
    QString fieldNames=T::GetMetaFieldNames();

    QString cmd=GETALL_CMD.arg(tableName()).arg(fieldNames);
    //zInfo("cmd:"+cmd);
    //QSqlQuery q = _sqlHelper.GetQuery(cmd);
    SQLHelper::DoQueryRModel rm = _globals._helpers._sqlHelper.DoQuery(cmd);

    QList<T> items;
    if(rm.hasRecords())
    {
        for(auto&r:rm.records)
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
    QString fieldList=SQLHelper::GetFieldNames_UPDATE(params);
    QString cmd=UPDATE_CMD.arg(tableName()).arg(fieldList);
    //zInfo("cmd:"+cmd);
    SQLHelper::DoQueryRModel rm = _globals._helpers._sqlHelper.DoQuery(cmd, params);

    // if(!rm.isOk){
    //     QString msg = rm.ToString();
    //     zWarning(msg);
    // }

    zInfo("records updated:"+QString::number(rm.recordCount()));
    return rm.isOk;
}

template<class T>
bool SqlRepository<T>::Add(const T &m){
    QList<SQLHelper::SQLParam> params = m.GetQueryParams(); // a modelosztályban van implementálva
    QString fieldList=SQLHelper::GetFieldNames_INSERT(params);
    QString paramList=SQLHelper::GetParamList_INSERT(params);

    QString cmd=INSERT_CMD.arg(tableName()).arg(fieldList).arg(paramList);
    //zInfo("cmd:"+cmd);
    SQLHelper::DoQueryRModel rm = _globals._helpers._sqlHelper.DoQuery(cmd, params);

    // if(!rm.isOk){
    //     QString msg = rm.ToString();
    //     zWarning(msg);
    // }

    zInfo("records inserted:"+QString::number(rm.recordCount()));
    return rm.isOk;
}

// template<typename T>
// bool SqlRepository<T>::dbErr(SQLHelper::DbErr &dbErr){
//     bool exists = isTableExists();
//     if(exists) return true;

//     QString t = tableName();
//     dbErr.AddError_TableNotExists(t);
//     return false;
// }

template<typename T>
bool SqlRepository<T>::isTableExists()
{
    QString dbName = _globals._helpers._sqlHelper.dbName();
    QString cmd=TABLE_EXISTS_CMD.arg(dbName).arg(tableName());
    //QString cmd="SELECT COUNT(*) FROM Article;";
    //QString cmd="sys.table_exists('biovitality', 'Article', @table_type);";
    //QString cmd1="SELECT @table_type;";
    //zInfo("cmd:"+cmd);
    SQLHelper::DoQueryRModel rm = _globals._helpers._sqlHelper.Call(cmd);
    //QList<QSqlRecord> records1 = _globals._helpers._sqlHelper.DoQuery(cmd1, {});

    bool isTable = false;
    if(rm.hasRecords())
    {
        auto r = rm.records.first();
        auto table_type = r.value(0).toString();
        //zInfo("table_type:"+table_type); //'BASE TABLE', 'VIEW', 'TEMPORARY'
        isTable = table_type == "BASE TABLE";
    }
    return isTable;
}

template<typename T>
bool SqlRepository<T>::isFieldsExists()
{
    QString dbName = _globals._helpers._sqlHelper.dbName();
    QString cmd=TABLE_EXISTS_CMD.arg(dbName).arg(tableName());
    SQLHelper::DoQueryRModel rm = _globals._helpers._sqlHelper.DoQuery(cmd);

    bool isFields = false;
    if(rm.hasRecords()){
        const T &m = T::metaInstance();
        QList<SQLHelper::SQLParam> params = m.GetQueryParams();
        QList<QSqlRecord>& records = rm.records;
        for (SQLHelper::SQLParam &p : params) {
            //p.fieldName
            if(records.contains(p.fieldName)){
                aaa
            }
            else{
                bbb
            }
        }
    }
    return isFields;
}

/**/

// template<typename T>
// const QString SqlERepository<T>::CONTAINS_EXCEL_ID_CMD =
//     QStringLiteral("SELECT EXISTS(SELECT 1 FROM %1 WHERE excelId = %2) AS _exists;");
// template<typename T>
// const QString SqlERepository<T>::GET_ID_BY_EXCEL_ID_CMD =
//     QStringLiteral("SELECT id FROM %1 WHERE excelId = %2;");

// template<typename T>
// bool SqlERepository<T>::ContainsBy_ExcelId(int id)
// {
//     bool exists = false;

//     QString cmd = CONTAINS_EXCEL_ID_CMD.arg(tableName2()).arg(id);
//     zInfo("cmd:"+cmd);
//     QList<QSqlRecord> records = _globals._helpers._sqlHelper.DoQuery(cmd);

//     if(!records.isEmpty()){
//         QVariant a = records.first().value("_exists");

//         exists = a.toBool();
//     } else{
//         bool isDbValid = _globals._helpers._sqlHelper.dbIsValid();
//         if(!isDbValid){
//             zWarning("db is invalid");
//         }
//     }

//     return exists;
// }

// template<typename T>
// int SqlERepository<T>::GetIdBy_ExcelId(int excelId)
// {
//     int id = -1;

//     QString cmd = GET_ID_BY_EXCEL_ID_CMD.arg(tableName2()).arg(excelId);
//     zInfo("cmd:"+cmd);
//     QList<QSqlRecord> records = _globals._helpers._sqlHelper.DoQuery(cmd);

//     if(!records.isEmpty()){
//         QVariant a = records.first().value("id");
//         bool ok;
//         int i = a.toInt(&ok);
//         if(ok) id = i;
//     }

//     return id;
// }

/*Contains_ByColumn*/
template<typename T>
bool SqlRepository<T>::Contains_ByColumn(const QString& fieldName, const QVariant& fieldValue)
{
    bool exists = false;
    QString cmd = CONTAINS_BY_COLUMN_CMD.arg(tableName()).arg(fieldName).arg(fieldValue.toString());
    //zInfo("cmd:"+cmd);
    SQLHelper::DoQueryRModel rm = _globals._helpers._sqlHelper.DoQuery(cmd);

    if(rm.hasRecords()){
        QVariant a = rm.records.first().value("_exists");
        exists = a.toBool();
    } else{
        bool isDbValid = _globals._helpers._sqlHelper.dbIsValid();
        if(!isDbValid){
            zWarning("db is invalid");
        }
    }
    return exists;
}


template<typename T>
QList<int> SqlRepository<T>::GetIds_ByColumn(const QString& fieldName, const QVariant& fieldValue)
{
    //int id = -1;
    QList<int> e;

    QString cmd = GET_ID_BY_COLUMN_CMD.arg(tableName()).arg(fieldName).arg(fieldValue.toString());
    //zInfo("cmd:"+cmd);
    SQLHelper::DoQueryRModel rm = _globals._helpers._sqlHelper.DoQuery(cmd);

    if(rm.hasRecords())
    {
        for(auto&record:rm.records)
        {
            QVariant a = record.value("id");
            bool ok;
            int i = a.toInt(&ok);
            if(ok)
            {
                e.append(i);
            }
        }
    }

    return e;
}

template<typename T>
bool SqlRepository<T>::Check(const QString& refTypeName)
{
    bool tableExists = false;
    bool fieldsExists = false;
    //T c = *(r2->metaInstance());
    RepositoryBase* rx = RepositoryBase::GetRepository(refTypeName);
    if(rx){
        SqlRepository<T>* repo = reinterpret_cast<SqlRepository<T>*>(rx);
        tableExists = repo->isTableExists();

        zInfo(QStringLiteral("tableExists") + (tableExists ? "ok" : "failed"));

        fieldsExists = repo->isFieldsExists();
    } else{
        zInfo(QStringLiteral("no refTypeName:") + refTypeName);
    }
    return tableExists;
}

RepositoryBase* RepositoryBase::GetRepository(const QString& tableName){
    for(auto r:_repos){
        if(r->_tableName == tableName) return r;
    }
    return nullptr;
}
