#include "mainpresenter_address.h"

#include "bi/address/addressoperations.h"
#include "bi/operationhelper.h"

#include "mvp/models/address.h"

MainPresenter_Address::MainPresenter_Address(QObject *parent):Presenter(parent){}

void MainPresenter_Address::Connect(QObject *view_obj)//, Presenter *p)
{
    //_presenter = p;
    /*ADDRESS*/
    // UI Form Add Address
    QObject::connect(view_obj, SIGNAL(Add_Address_ActionTriggered(IMainView *)),
                     this, SLOT(process_CreateAddress_Action(IMainView *)));

    QObject::connect(view_obj, SIGNAL(Update_Address_ActionTriggered(IMainView *)),
                     this, SLOT(process_UpdateAddress_Action(IMainView *)));

    // CSV_Import Address - Cím
    QObject::connect(view_obj, SIGNAL(CimImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_ImportAddress_Action(IMainView *)));

    // Address List
    QObject::connect(view_obj, SIGNAL(AddressList_ActionTriggered(IMainView *)),
                     this, SLOT(process_ListAddress_Action(IMainView *)));

}


/*ADDRESS*/

// Create
void MainPresenter_Address::process_CreateAddress_Action(IMainView *sender){
    zTrace();
    AddressOperations::Operation_InsertAddress(this, sender);
}

// Update
void MainPresenter_Address::process_UpdateAddress_Action(IMainView *sender){
    zTrace();

    AddressOperations::Operation_UpdateAddress(this, sender, QUuid(), 2);
}

// ReadAll
void MainPresenter_Address::process_ListAddress_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    ListModel<Address>* model = new ListModel<Address>();

    AddressList *adl = new AddressList();

    model->setAddressList(adl);

    //model->amType = AddModel_Type::Update;
    Operations::instance().setData(opId, model);

    adl->List_Address(opId, this);
}

// Accept Create/Update
void MainPresenter_Address::process_AcceptAddress_Action(QUuid opId)
{
    zTrace();
    auto e = OperationHelper::process_CreateUpdate_AcceptAction<Address>(opId);
    if(e.type!=OperationHelper::AcceptActionType::None)
    {
        ListModel<Address> *model = Operations::instance().data<ListModel<Address>> (e.parentId);
        if(model)
        {
            DataListForm *form = model->dataListForm();
            if(form)
            {
                if(e.type==OperationHelper::AcceptActionType::AddRow){
                    emit  form->TableFresh_AddRow(e.parentId, e.m_values);
                } else if(e.type==OperationHelper::AcceptActionType::UpdateRow){
                    emit  form->TableFresh_UpdateRow(e.parentId, e.m_values);
                }
            }
        }
    }
}

void MainPresenter_Address::process_DoneAddress_Action(QUuid opId, int r){
    zTrace();
}

// Import

void MainPresenter_Address::process_ImportAddress_Action(IMainView *sender)
{
    zTrace();
    AddressOperations::Import1Result a = AddressOperations::Operation_ImportAddress1(this, sender);

    if(a.isValid())
    {
        MainViewModel::FileNameModel fn = sender->get_CSVFileName_Address();
        if(fn.IsValid())
        {
            AddressOperations::Operation_ImportAddress2(fn);
        }
    }
    Operations::instance().stop(a.opId());
}
