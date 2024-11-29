// #include <helpers/filehelper.h>
// #include <helpers/sqlhelper.h>
// #include "csv_sqlhelper.h"
// #include "sqlmetahelper.h"

// template<typename T>
// void CSV_SQLHelper::Import(const QString& fn, SqlRepository<T>& repo){
//     CSVErrModel csverr(fn);
//     FileHelper::CSVModel csvModel = FileHelper::LoadCSV(fn, ',');
//     csverr.setRecordsCount(csvModel.records.count());

//     if(csvModel.error == FileHelper::Ok)
//     {
//         zInfo("file ok");
//         QList<T> items = T::CSV_Import(csvModel.records);
//         csverr.setItemsCount(items.count());

//         zInfo("items loaded: "+csverr.ToSting());
//         SqlMetaHelper::InsertOrUpdate2(repo, items, "countryCode");
//     }
//     else
//     {
//         zWarning("items load failed: "+csverr.ToSting());
//     }
// }
