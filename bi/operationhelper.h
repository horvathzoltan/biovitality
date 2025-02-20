#ifndef OPERATIONHELPER_H
#define OPERATIONHELPER_H

#include <mvp/viewmodels/mainviewmodel.h>
#include "../../meta/csv_sqlhelper.h"
#include "bi/operations.h"

class OperationHelper
{
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

signals:
    void TableFresh_AddRow(QUuid opid,const  QList<MetaValue>& values);
    void TableFresh_UpdateRow(QUuid opid,const QList<MetaValue>& values);




    template<typename T>
    static void process_CreateUpdate_AcceptAction(QUuid opId)
    {
        zTrace();
        //void *a = Operations::instance().data(opId);
        //FormModel<T> *b = reinterpret_cast<FormModel<T>*>(a);
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
                                //  001a kell a row data is átadni, beszúrjuk a rowt a végére
                                emit TableFresh_AddRow(parentId, m.values);
                            }
                        }
                    } else if(b->IsUpdate()){
                        // UPDATE
                        bool updated = repo->Update(data);
                        if(updated){
                            //QUuid parentId = Operations::instance().parentId(opId);
                            if(!parentId.isNull()){
                                //  001b kell a row data is átadni, felupdateljük a rowt
                                emit TableFresh_UpdateRow(parentId, m.values);
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
    }
};
#endif // OPERATIONHELPER_H
