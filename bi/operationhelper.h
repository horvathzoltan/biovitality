#ifndef OPERATIONHELPER_H
#define OPERATIONHELPER_H

#include <mvp/viewmodels/mainviewmodel.h>

class OperationHelper
{
public:
    template<typename T>
    static void Import_private(const MainViewModel::FileNameModel& fn,
                               //SqlRepository<T>& repo,
                               const QString& keyColumnName,
                               const QChar& separator);
};

#endif // OPERATIONHELPER_H
