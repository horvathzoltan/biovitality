#ifndef OPERATIONHELPER_H
#define OPERATIONHELPER_H

#include <mvp/viewmodels/mainviewmodel.h>
#include "../../meta/csv_sqlhelper.h"

class OperationHelper
{
public:
    template<typename T>
    // static void Import_private(const MainViewModel::FileNameModel& fn,
    //                            //SqlRepository<T>& repo,
    //                            const QString& keyColumnName,
    //                            const QChar& separator)

    static void Import_private(const MainViewModel::FileNameModel& fn,
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

};

#endif // OPERATIONHELPER_H
