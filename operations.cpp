#include "operations.h"

//Operations::Operations() {}

QUuid Operations::startNew(Presenter *presenter, IView *sender, const QString& name)
{
    Operation o;
    o.id = QUuid::createUuid();
    o.presenter = presenter;
    o.view = sender;
    o.name = name;
    _operations.insert(o.id, o);
    zInfo("operation "+name+ " started");
    return o.id;
}

void Operations::stop(QUuid id)
{
    bool contains = _operations.contains(id);
    if(contains){
        auto o = _operations.value(id);
        _operations.remove(id);
        zInfo("operation "+o.name+ " started");
    } else {
        zInfo("no operation:"+id.toString());
    }
}

void Operations::setData(QUuid id, OperationModel* m)
{
    bool contains = _operations.contains(id);
    if(contains){
        auto& o = _operations[id];
        o._data = m;
        zInfo("operation "+o.name+ " added data");
    } else {
        zInfo("no operation:"+id.toString());
    }
}


OperationModel* Operations::data(QUuid id)
{
    bool contains = _operations.contains(id);
    if(contains){
        auto& o = _operations[id];
        return o._data;
        zInfo("operation "+o.name+ " added data");
    } else {
        zInfo("no operation:"+id.toString());
    }
    return nullptr;
}
