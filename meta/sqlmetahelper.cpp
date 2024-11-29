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



// template<typename T>
// void SqlMetaHelper::InsertOrUpdate(SqlRepository<T>& repo, QList<T>& items)
// {
//     if(items.isEmpty()){
//         zInfo("no items to import");
//         return;
//     }

//     int i_all=0, u_all=0;
//     int i_ok=0, u_ok=0;
//     for(auto&i:items){
//         bool contains = repo.ContainsBy_ExcelId(i.excelId);
//         if(contains){
//             int id =  repo.GetIdBy_ExcelId(i.excelId); // meg kell szerezni az id-t
//             if(id!=-1)
//             {
//                 i.id = id;
//                 u_all++;
//                 bool ok =  repo.Update(i);
//                 if(ok) u_ok++;
//             } else{
//                 zInfo("no id for excelId: "+QString::number(i.excelId));
//             }
//         } else{
//             i_all++;
//             bool ok =  repo.Add(i);
//             if(ok) i_ok++;
//         }
//     }

//     zInfo(QStringLiteral("Updated: %1/%2").arg(u_ok).arg(u_all));
//     zInfo(QStringLiteral("Inserted: %1/%2").arg(i_ok).arg(i_all));
// }


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

