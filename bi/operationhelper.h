#ifndef OPERATIONHELPER_H
#define OPERATIONHELPER_H

#include <mvp/viewmodels/mainviewmodel.h>
#include "../../meta/csv_sqlhelper.h"
#include "bi/operations.h"

class OperationHelper//: public QObject
{
//    Q_OBJECT

public:
    template<typename T>
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

    enum AcceptActionType:int
    {
        None = 0,
        AddRow,
        UpdateRow
    };

    struct AcceptActionResponse{
        AcceptActionType type = None;
        QUuid opId;
        QUuid parentId;
        QList<MetaValue> m_values;

        explicit AcceptActionResponse(QUuid o) : opId(o){};

        private:
        AcceptActionResponse(){};
    };

    template<typename T>
    static AcceptActionResponse process_CreateUpdate_AcceptAction(QUuid opId)
    {
        zTrace();
        AcceptActionResponse e(opId);

        FormModel<T> *b = Operations::instance().data<FormModel<T>>(opId);

        if(b){
            DataForm::DataModel m = b->Get_MetaValues();
            if(m.isValid()){
                b->dataForm_done(1);
                // itt van az hogy le kéne a változtatott rekordot menteni
                T data = T::Meta().FromMetaValues(m.values);

                SqlRepository<T> *repo = //_globals._repositories.address;
                    SqlRepositoryContainer::Get<T>();

                if(repo)
                {
                    QUuid parentId = Operations::instance().parentId(opId);
                    if(b->IsCreate()){
                        // CREATE
                        bool added = repo->Add(data);
                        if(added){
                            if(!parentId.isNull())
                            {
                                e.m_values = m.values;
                                e.parentId = parentId;
                                e.type = AddRow;
                            }
                        }
                    } else if(b->IsUpdate()){
                        // UPDATE
                        bool updated = repo->Update(data);
                        if(updated){
                            if(!parentId.isNull())
                            {
                                e.m_values = m.values;
                                e.parentId = parentId;
                                e.type = UpdateRow;
                            }
                        }
                    };
                }

                Operations::instance().stop(opId);
            }
            else{
                b->dataForm_Set_Validations(m.validations);
                QStringList e = m.Get_LogMessages();
                zWarning(e.join('\n'));
            }
        }
        //Operations::instance().stop(opId);
        return e;
    }

};
#endif // OPERATIONHELPER_H
