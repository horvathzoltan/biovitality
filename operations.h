#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "bi/models/solditem.h"
#include "helpers/logger.h"
#include "presenter.h"

#include <QString>
#include <QUuid>
#include <IView.h>
#include <Singleton.h>
#include <QMap>

class OperationModel{

};

class AddSoldItemModel: public OperationModel
{
public:
    //QUuid opId
    SoldItem data;
};

class Operations :public Singleton<Operations>
{
public:
    class Operation{
    public:
        QUuid id;
        Presenter* presenter;
        IView* view;
        QString name;

        OperationModel* _data;
    };
private:
    QMap<QUuid, Operation> _operations;
public:
    QUuid startNew(Presenter *presenter, IView *sender, const QString& name);
    void stop(QUuid id);

    void setData(QUuid id, OperationModel* m);
    OperationModel* data(QUuid id);
};

#endif // OPERATIONS_H
