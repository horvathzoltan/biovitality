#include "sqlmetahelper.h"

#include <QSqlField>


QList<MetaValue> SqlMetaHelper::RecordToMetaValues(const QSqlRecord& r)
{
    if(r.isEmpty()) return {};

    QList<MetaValue> m;
    int L = r.count();
    for(int i=0;i<L;i++){
        QSqlField f = r.field(i);
        MetaValue v(f.name(), "", f.metaType());
        //v.name = f.name();
        v.value = f.value();
        m.append(v);
    }
    return m;
}

// QMap<QString,QVariant> SqlMetaHelper::RecordToMetaValues2(const QSqlRecord& r)
// {
//     if(r.isEmpty()) return {};

//     QMap<QString,QVariant> m;
//     int L = r.count();
//     for(int i=0;i<L;i++){
//         QSqlField f = r.field(i);
//         m.insert(f.name(), QVariant(f.metaType()));
//     }
//     return m;
// }

// void SqlMetaHelper::Prepare(QSqlQuery *q, const QString& cmd, const QList<MetaValue>& metaValues)
// {
//     if(!q) return;
//     q->prepare(cmd);

//     for(auto&m:metaValues){
//         q->bindValue(":"+m.name, m.value);
//     }
// }
