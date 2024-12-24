#ifndef SQLMETAHELPER_H
#define SQLMETAHELPER_H


#include <meta/meta.h>
#include <QSqlQuery>
#include <QSqlRecord>
#include "repositories/sqlrepository.h"
#include "csvhelper.h"
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


    // ha nincs keyColumn akkor nem lehet updatelni, mert nincsen mező amiben a kulcs értéke lenne
    // ha a keycolumn értéke null, vagy -1(int) nem lehet updatelni, mert nem lesz -1-es kulcsú rekord

    template<typename T>
    static void InsertOrUpdate2(SqlRepository<T>& repo,
                                CSV_ImportModel<T>& m,
                                const QString& keyColumnName)
    {
        if(m.isEmpty()){
            zInfo("no items to import");
            return;
        }
        //if(keyColumnName.isEmpty()){}
        //{
        //     zInfo("no columnName to import");
        //     return;
        // }

        bool hasKeyColumn = keyColumnName.isEmpty();

        int i_all=0, u_all=0;
        int i_ok=0, u_ok=0;
        for(auto&data:m.data()){
            // MetaField* columnMetaField = i.GetField(columnName);
            // MetaValue columnMetaValue = columnMetaField->GetMetaValue(&i);
            QString csvRow = data.csvRow();
            int rowNumber = data.rowNumber();
            if(!data.isValid()){
                zInfo("row "+QString::number(rowNumber)+" is invalid: \""+csvRow+"\"");
                continue;
            } else{
                zInfo("row "+QString::number(rowNumber)+": \""+csvRow+"\"");
            }

            T item = data.item();


            QString msg = "item";

            QVariant keyColumnValue;
            bool canUpdate = false;
            bool contains = false;
            if(hasKeyColumn)
            {
                msg+= " key: "+keyColumnName;
                keyColumnValue = T::Meta().GetValue(&item, keyColumnName);
                if(keyColumnValue.isValid())
                {
                    msg += "="+keyColumnValue.toString();
                    canUpdate = keyColumnValue!=-1 && keyColumnValue!="";
                    if(canUpdate)
                    {
                        contains = repo.Contains_ByColumn(keyColumnName, keyColumnValue);
                    }
                }
            }
            else
            {
                  msg += " has no key";
            }

            zInfo(msg);

            if(contains)
            {
                zInfo("record update");
                QList<int> ids =  repo.GetIds_ByColumn(keyColumnName, keyColumnValue); // meg kell szerezni az id-t
                int count = ids.count();
                if(count == 1)
                {                    
                    item.id = ids.first();
                    u_all++;
                    bool ok = repo.Update(item);
                    if(ok) u_ok++;
                    zInfo(QStringLiteral("record update:") +(ok?"ok":"failed"));
                } else if(count == 0){
                    zInfo("no record exists:"+keyColumnName+"="+keyColumnValue.toString());
                } else{
                    zInfo("record is not unique:"+keyColumnName+"="+keyColumnValue.toString());
                }
            }
            else
            {
                zInfo("record insert");
                i_all++;
                bool ok =  repo.Add(item);
                if(ok) i_ok++;
                zInfo(QStringLiteral("record insert:") +(ok?"ok":"failed"));
            }
        }

        zInfo(QStringLiteral("Updated: %1/%2").arg(u_ok).arg(u_all));
        zInfo(QStringLiteral("Inserted: %1/%2").arg(i_ok).arg(i_all));
    }
};

#endif // SQLMETAHELPER_H
