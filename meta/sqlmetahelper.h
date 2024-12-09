#ifndef SQLMETAHELPER_H
#define SQLMETAHELPER_H


#include <meta/meta.h>
#include <QSqlQuery>
#include <QSqlRecord>
#include "repositories/sqlrepository.h"
//#include "mvp/models/partner.h"

class SqlMetaHelper
{
public:
    static QList<MetaValue> RecordToMetaValues(const QSqlRecord& r);
    //static QMap<QString,QVariant> RecordToMetaValues2(const QSqlRecord& r);

    //static void Prepare(QSqlQuery* q, const QString& cmd, const QList<MetaValue>& m);
    // template<typename T>
    // static void InsertOrUpdate(SqlRepository<T>& repo, QList<T>& items);

   // extern template void InsertOrUpdate_ByExcelId(SqlRepository<Partner>& repo, QList<Partner>& items);
    // template<typename T>
    // static void InsertOrUpdate_ByExcelId(SqlERepository<T>& repo, QList<T>& items)
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

    template<typename T>
    static void InsertOrUpdate2(SqlRepository<T>& repo, QList<T>& items, const QString& keyColumnName)
    {
        if(items.isEmpty()){
            zInfo("no items to import");
            return;
        }
        // if(columnName.isEmpty()){
        //     zInfo("no columnName to import");
        //     return;
        // }

        int i_all=0, u_all=0;
        int i_ok=0, u_ok=0;
        for(T&i:items){
            // MetaField* columnMetaField = i.GetField(columnName);
            // MetaValue columnMetaValue = columnMetaField->GetMetaValue(&i);
            QVariant keyColumnValue = i.GetValue(keyColumnName);
            //if(!columnMetaValue.isValid()) continue;

            bool canUpdate = keyColumnValue.isValid() && (keyColumnValue!=-1 && keyColumnValue!="");
            zInfo("item: "+ keyColumnName+" = "+keyColumnValue.toString());

            bool contains = repo.Contains_ByColumn(keyColumnName, keyColumnValue);
            if(contains && canUpdate){
                zInfo("record update");
                QList<int> ids =  repo.GetIds_ByColumn(keyColumnName, keyColumnValue); // meg kell szerezni az id-t
                int count = ids.count();
                if(count == 1)
                {                    
                    i.id = ids.first();
                    u_all++;
                    bool ok = repo.Update(i);
                    if(ok) u_ok++;
                    zInfo(QStringLiteral("record update:") +(ok?"ok":"failed"));
                } else if(count == 0){
                    zInfo("no record exists:"+keyColumnName+"="+keyColumnValue.toString());
                } else{
                    zInfo("record is not unique:"+keyColumnName+"="+keyColumnValue.toString());
                }
            } else{
                zInfo("record insert");
                i_all++;
                bool ok =  repo.Add(i);
                if(ok) i_ok++;
                zInfo(QStringLiteral("record insert:") +(ok?"ok":"failed"));
            }
        }

        zInfo(QStringLiteral("Updated: %1/%2").arg(u_ok).arg(u_all));
        zInfo(QStringLiteral("Inserted: %1/%2").arg(i_ok).arg(i_all));
    }
};

#endif // SQLMETAHELPER_H
