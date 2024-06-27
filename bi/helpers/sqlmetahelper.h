#ifndef SQLMETAHELPER_H
#define SQLMETAHELPER_H

#include <bi/meta/meta.h>
#include <QSqlQuery>
#include <QSqlRecord>


class SqlMetaHelper
{
public:
    static QList<MetaValue> RecordToMetaValues(const QSqlRecord& r);

    static void Prepare(QSqlQuery* q, const QString& cmd, const QList<MetaValue>& m);
};

#endif // SQLMETAHELPER_H
