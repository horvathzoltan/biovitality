#include "addresslist.h"
#include "addressoperations.h"
#include "../operations.h"
#include "../../infrastructure/globals.h"
#include "../../mvp/models/address.h"
#include "../../mvp/models/county.h"
#include "../../repositories/sqlrepository.h"

extern Globals _globals;

AddressList::AddressList(QObject *parent):QObject(parent) {}

/*
*
*/
void AddressList::List_Address(QUuid opId, Presenter *presenter)
{
    //void *a = Operations::instance().data(opId);
    //ListModel<Address> *model = reinterpret_cast<ListModel<Address>*>(a);
    ListModel<Address> *model = Operations::instance().data<ListModel<Address>>(opId);

    if(model)
    {
        auto addressRepo = _globals._repositories.address;
        bool connected = _globals._helpers._sqlHelper.TryConnect();
        if(connected)
        {
            bool isRepoOk = SqlRepository<Address>::Check();
            bool ref1Ok_County = CheckRef(Address, countyId, County);

            bool refOk_Country = CheckRef(Address, countryId, Country);

            bool valid = isRepoOk
                         && ref1Ok_County //&& ref2Ok_County && ref3Ok_County
                         && refOk_Country ;
            if(valid)
            {
                DataListForm* form = new DataListForm(opId);

                QString title = _tr(WCodes::List)+": "+_tr(WCodes::Address);
                form->setWindowTitle(title);

                auto h0 =  Address::Meta().ToMetaValues(Address::Meta()._instance);
                form->setHeaderLine(h0);

                //referenciákat lekérjük id alapján

                QList<Address> data = _globals._repositories.address.GetAll();
                //model->data = data;

                // ez a mezők neveit és azok típusát tartalmazza
                // referencia esetén a value a hivatkozott id,

                    QList<QList<MetaValue>> m = Address::Meta().ToMetaValueList(data);
                form->setMetaValueList(m);

                DataRowDefaultModel countyRows = Get_DataRowDefaultModel(Address, countyId, County);
                DataRowDefaultModel countryRows = Get_DataRowDefaultModel(Address, countryId, Country);
                QList<DataRowDefaultModel> defaults {countyRows, countryRows};
                form->SetDataRowDefaults(defaults);

                form->show();

                QObject::connect(form, SIGNAL(UpdateActionTriggered(QUuid, int)),
                                 this, SLOT(process_UpdateAction(QUuid, int)));

                QObject::connect(form, SIGNAL(InsertActionTriggered(QUuid)),
                                 this, SLOT(process_InsertAction(QUuid)));

                QObject::connect(presenter, SIGNAL(TableFresh_AddRow(QUuid, const  QList<MetaValue>&)),
                                 this, SLOT(process_TableFresh_AddRow(QUuid, const  QList<MetaValue>&)));

                QObject::connect(presenter, SIGNAL(TableFresh_UpdateRow(QUuid, const  QList<MetaValue>&)),
                                 this, SLOT(process_TableFresh_UpdateRow(QUuid, const  QList<MetaValue>&)));

                QObject::connect(form, SIGNAL(DoneActionTriggered(QUuid, int)),
                                 this, SLOT(process_DoneAction2(QUuid, int)));

                model->Set_data(form, data);

            }
        }
    }
}

void AddressList::process_UpdateAction(QUuid opId, int id)
{
    zTrace();

    Operation *a = Operations::instance().operation(opId);
    AddressOperations::Operation_UpdateAddress(a->presenter(), a->view(), opId, id);
}

void AddressList::process_InsertAction(QUuid opId)
{
    zTrace();

    Operation *a = Operations::instance().operation(opId);
    AddressOperations::Operation_InsertAddress(a->presenter(), a->view());
}

void AddressList::process_TableFresh_AddRow(QUuid opId, const QList<MetaValue>& values)
{
    //zTrace();
    ListModel<Address> *model = Operations::instance().data<ListModel<Address>>(opId);
    if(!model) return;
    DataListForm *d = model->dataListForm();
    if(!d) return;

    d->AddRow(values);
}


void AddressList::process_TableFresh_UpdateRow(QUuid opId, const QList<MetaValue>& values)
{
    //zTrace();
    ListModel<Address> *model = Operations::instance().data<ListModel<Address>>(opId);
    if(!model) return;
    DataListForm *d = model->dataListForm();
    if(!d) return;

    d->UpdateRow(values);
}


void AddressList::process_DoneAction2(QUuid opId, int r){
    zTrace();

    QObject::disconnect(this, SIGNAL(TableFresh()),
                        this, SLOT(process_TableFresh()));

    Operations::instance().stop(opId);
}
