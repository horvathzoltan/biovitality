#include "operations.h"

Operation::Operation(){
    _data = nullptr;
    //_typeIndex = std::type_index(typeid(void*));
    _presenter = nullptr;
    _view = nullptr;
}

Operation::Operation(QUuid parentId, Presenter *presenter, IView *sender, const QString &name)
{
    _id = QUuid::createUuid();
    _presenter = presenter;
    _view = sender;
    _name = name;
    _data = nullptr;
    //_dataType = QMetaType::UnknownType;
    //_typeIndex = std::type_index(typeid(void*));
    _parentId = parentId;
}




// void Operation::setData(void* m, std::type_index _typeIndex)
// {
//     _data = m;
//     //_dataType = QMetaType::fromType<decltype(m)>().type();
// }

// Operation Operations::startNew_private(Presenter *presenter, IView *sender, const QString &name)
// {
//     Operation(QUuid::createUuid(), presenter, sender, name);
//     return o;
// }

QUuid Operations::startNew(Presenter *presenter, IView *sender, const QString& name)
{
    Operation o(QUuid(), presenter, sender, name);

    QUuid id = o.id();
    _operations.insert(id, o);
    zInfo("operation "+name+ " started: " + id.toString());
    return id;
}

QUuid Operations::startNew(Presenter *presenter, IView *sender, const QString &name, QUuid parentId)
{
     Operation o(parentId,presenter, sender, name);

     QUuid id = o.id();
     _operations.insert(id, o);
     zInfo("operation "+name+ " started: " + id.toString());
     return id;
}

void Operations::stop(QUuid id)
{    
    bool contains = _operations.contains(id);
    if(contains){
        QString name = _operations.value(id).name();

        _operations.remove(id);
        zInfo("operation " + name + " stopped: " + id.toString());
    } else {
        zWarning("no operation: "+id.toString());
    }
}

// void Operations::setData(QUuid id, void* m, std::type_index typeIx)
// {
//     Operation *o = operation(id);
//     if(o){
//         o->setData(m, typeIx);
//         zInfo("operation "+o->name()+ " added data: "+ id.toString());
//     } else {
//         zInfo("no operation: "+id.toString());
//     }
// }


// void* Operations::data(QUuid id)
// {
//     Operation *o = operation(id);
//     if(o){
//         zInfo("operation "+o->name()+ " find data: "+id.toString());
//         return o->data();
//     }

//     zInfo("no operation: "+id.toString());
//     return nullptr;
// }

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
        zInfo("operation "+o->name()+ " find data: "+id.toString());
        return o->parentId();
    }

    zInfo("no operation: "+id.toString());
    return QUuid();
}




// template<typename T>
// void Operations::setData(QUuid id, T *m)
// {
//     Operation *o = operation(id);
//     if(o){
//         o->setData(m);
//         zInfo("operation "+o->name()+ " added data: "+ id.toString());
//     } else {
//         zInfo("no operation: "+id.toString());
//     }
// }




// template<typename T>
// T *Operations::data(QUuid id)
// {
//     Operation *o = operation(id);
//     if(o){
//         zInfo("operation "+o->name()+ " find data: "+id.toString());
//         return o->data<T>();
//     }

//     zInfo("no operation: "+id.toString());
//     return nullptr;
// }
