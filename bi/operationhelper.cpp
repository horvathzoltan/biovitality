#include "operationhelper.h"
#include "../../meta/csv_sqlhelper.h"

template<typename T>
void OperationHelper::Import_private(const MainViewModel::FileNameModel& fn,
                                       //SqlRepository<T>& repo,
                                       const QString& keyColumnName,
                                       const QChar& separator)
{
    if(!fn.isCanceled){
        CSV_SQLHelper::Import<T>(fn.fileName, keyColumnName, separator);
    } else{
        zInfo("cancelled");
    }
}
