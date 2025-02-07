#ifndef OPERATIONS_H
#define OPERATIONS_H

#include <typeindex>

#include "mvp/models/solditem.h"
#include "helpers/logger.h"
#include "mvp/views/dataform.h"
#include "mvp/views/datalistform.h"
#include "mvp/presenters/presenter.h"

#include <QString>
#include <QUuid>
#include <mvp/viewinterfaces/iview.h>
#include <patterns/singleton.h>
#include <QMap>
#include <helpers/translator.h>

// class OperationModel{

// };

enum FormModel_Type{ Create, Update };

template<class T>
class FormModel//: public OperationModel
{
public:
    FormModel(FormModel_Type amType, int id){
        _amType = amType;
        _id = id;
    };
    ~FormModel(){
        zTrace();
        delete _dataForm;
    };
private:
    FormModel(){};

    T _data;
    DataForm* _dataForm;
    int _id = -1;
    FormModel_Type _amType;

public:
    int Id(){return _id;};

    QString GetOpname()
    {
        if(_amType == FormModel_Type::Create) return GetWCode(WCodes::AddNew);
        if(_amType == FormModel_Type::Update) return GetWCode(WCodes::Update);
        return "unknown";
    }

    bool IsUpdate(){return _amType == FormModel_Type::Update;};
    bool IsCreate(){return _amType == FormModel_Type::Create;};

    void Set_data(DataForm *f, const T& d){
        zTrace();
        _dataForm = f;
        _data = d;
    };

    DataForm::DataModel Get_MetaValues(){return _dataForm->Get_MetaValues();}
    void dataForm_done(int i){_dataForm->done(i);};

    void dataForm_Set_Validations(const QList<MetaValidationMessage>& v){_dataForm->SetValidations(v);}
};

template<class T>
class ListModel//: public OperationModel
{
private:
    ~ListModel(){
        _data.clear();
        delete _dataListForm;
    }
    QList<T> _data;
    DataListForm* _dataListForm;    
    //AddModel_Type amType;
public:
    //int CurrentId(){return _dataListForm->CurrentId();};
    void Set_data(DataListForm *f, const QList<T>& d){
        _dataListForm = f;
        _data = d;
    }
};

class Operation{
private:
    QUuid _id;
    QUuid _parentId;
    Presenter* _presenter;
    IView* _view;
    QString _name;
    void* _data;
    //QMetaType::Type _dataType;
    std::type_index _typeIndex;// = std::type_index(typeid(void*));
public:
    Operation();
    Operation(QUuid parentId, Presenter *presenter, IView *sender, const QString &name);

    QUuid id(){return _id;}
    QUuid parentId(){return _parentId;}
    Presenter* presenter(){return _presenter;}
    IView* view(){return _view;}
    QString name(){return _name;}
    void* data(){return _data;}
    void setData(void* m, std::type_index _typeIndex);
};

class Operations :public Singleton<Operations>
{
private:
    QMap<QUuid, Operation> _operations;

    //Operation startNew_private(Presenter *presenter, IView *sender, const QString& name);
public:

    QUuid startNew(Presenter *presenter, IView *sender, const QString& name);
    QUuid startNew(Presenter *presenter, IView *sender, const QString& name, QUuid parentId);
    void stop(QUuid id);

    void setData(QUuid id, void* m, std::type_index typeIx);
    void* data(QUuid id);
    Operation* operation(QUuid id);
    QUuid parentId(QUuid id);
};

#endif // OPERATIONS_H
