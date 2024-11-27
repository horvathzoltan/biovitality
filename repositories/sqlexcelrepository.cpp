// #include "sqlexcelrepository.h"
// #include "infrastructure/globals.h"
// #include "helpers/logger.h"
// #include <helpers/sqlhelper.h>

// #include <QSqlRecord>
// #include <QVariant>

// extern Globals _globals;

// const QString SqlExcelRepository::CONTAINS_EXCEL_ID_CMD =
//     QStringLiteral("SELECT EXISTS(SELECT 1 FROM %1 WHERE excelId = %2) AS _exists;");
// const QString SqlExcelRepository::GET_ID_BY_EXCEL_ID_CMD =
//     QStringLiteral("SELECT id FROM %1 WHERE excelId = %2;");

// bool SqlExcelRepository::ContainsBy_ExcelId(int id)
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

// int SqlExcelRepository::GetIdBy_ExcelId(int excelId)
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

