#include "sqlmetahelper.h"

#include <QSqlField>


QList<MetaValue> SqlMetaHelper::RecordToMetaValues(const QSqlRecord& r)
{
    if(r.isEmpty()) return {};

    QList<MetaValue> m;
    int L = r.count();
    for(int i=0;i<L;i++){
        QSqlField f = r.field(i);
        MetaValue v;
        v.name = f.name();
        v.value = f.value();
        m.append(v);
    }
    return m;
}
