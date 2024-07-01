#include "sqlexcelrepository.h"
#include "helpers/logger.h"
#include <helpers/sqlhelper.h>

#include <QSqlRecord>
#include <QVariant>

extern SQLHelper _sqlHelper;

const QString SqlExcelRepository::CONTAINS_EXCEL_ID_CMD =
    QStringLiteral("SELECT EXISTS(SELECT 1 FROM %1 WHERE excelId = %2) AS _exists;");

bool SqlExcelRepository::ContainsBy_ExcelId(int id)
{
    bool exists = false;

    QString cmd = CONTAINS_EXCEL_ID_CMD.arg(tableName2()).arg(id);
    zInfo("cmd:"+cmd);
    QList<QSqlRecord> records =_sqlHelper.DoQuery(cmd);

    if(!records.isEmpty()){
        QVariant a = records.first().value("_exists");

        exists = a.toBool();
    }

    return exists;
}
