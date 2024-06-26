#ifndef SQLMETAHELPER_H
#define SQLMETAHELPER_H

#include <bi/meta/meta.h>
#include <QSqlRecord>


class SqlMetaHelper
{
public:
    static QList<MetaValue> RecordToMetaValues(const QSqlRecord& r);
};

#endif // SQLMETAHELPER_H
