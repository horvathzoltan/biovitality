#ifndef OPERATIONS_H
#define OPERATIONS_H

#include "helpers/logger.h"
#include "presenter.h"

#include <QString>
#include <QUuid>
#include <IView.h>
#include <Singleton.h>
#include <QMap>

class Operations :public Singleton<Operations>
{
public:
    class Operation{
    public:
        QUuid id;
        Presenter* presenter;
        IView* view;
        QString name;
    };
private:
    QMap<QUuid, Operation> _operations;
public:
    QUuid start(Presenter *presenter, IView *sender, const QString& name);
    void stop(QUuid id);
};

#endif // OPERATIONS_H
