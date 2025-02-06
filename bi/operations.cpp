#include "operations.h"

//Operations::Operations() {}

QUuid Operations::startNew(Presenter *presenter, IView *sender, const QString& name)
{
    Operation o;
    o.id = QUuid::createUuid();
    o.presenter = presenter;
    o.view = sender;
    o.name = name;
    o._data = nullptr;
    _operations.insert(o.id, o);
    zInfo("operation "+name+ " started: " + o.id.toString());
    return o.id;
}

void Operations::stop(QUuid id)
{    
    bool contains = _operations.contains(id);
    if(contains){
        QString name = _operations.value(id).name;

        _operations.remove(id);
        zInfo("operation " + name + " stopped: " + id.toString());
    } else {
        zWarning("no operation: "+id.toString());
    }
}

void Operations::setData(QUuid id, void* m)
{
    Operation *o = operation(id);
    if(o){
        o->_data = m;
        zInfo("operation "+o->name+ " added data: "+ id.toString());
    } else {
        zInfo("no operation: "+id.toString());
    }
}


void* Operations::data(QUuid id)
{
    Operation *o = operation(id);
    if(o){
        zInfo("operation "+o->name+ " find data: "+id.toString());
        return o->_data;
    }

    zInfo("no operation: "+id.toString());
    return nullptr;
}

Operation* Operations::operation(QUuid id)
{
    bool contains = _operations.contains(id);
    if(contains){
        Operation* o = &_operations[id];
        return o;
    }
    return nullptr;
}

QUuid Operations::parentId(QUuid id)
{
    Operation *o = operation(id);
    if(o){
        zInfo("operation "+o->name+ " find data: "+id.toString());
        auto p = o->parentId;
        return p;
    }

    zInfo("no operation: "+id.toString());
    return QUuid();
}
