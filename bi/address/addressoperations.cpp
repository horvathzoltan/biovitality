#include "addressoperations.h"

#include "infrastructure/globals.h"
#include "mvp/models/address.h"
#include "../operations.h"
#include "../operationhelper.h"

extern Globals _globals;

void AddressOperations::Operation_UpdateAddress(Presenter *presenter, IView *sender, QUuid parent_opId, int id){
    //Operation *a = Operations::instance().operation(parent_opId);

    QUuid opId = Operations::instance().startNew(presenter, sender, __FUNCTION__, parent_opId);

    FormModel<Address>* model = new FormModel<Address>(FormModel_Type::Update, id);
    Operations::instance().setData(opId, model);

    CreateUpdate_Address(opId);
}

void AddressOperations::Operation_InsertAddress(Presenter *presenter, IView *sender)
{
    //Operation *a = Operations::instance().operation(parent_opId);

    QUuid opId = Operations::instance().startNew(presenter, sender, __FUNCTION__);

    FormModel<Address>* model = new FormModel<Address>(FormModel_Type::Create, -1);
    Operations::instance().setData(opId, model);

    CreateUpdate_Address(opId);
}

void AddressOperations::CreateUpdate_Address(QUuid opId)
{
    Operation *a = Operations::instance().operation(opId);
    //FormModel<Address> *model = reinterpret_cast<FormModel<Address>*>(a);
    FormModel<Address> *model = Operations::instance().data<FormModel<Address>>(opId);

    if(model)
    {
        auto addressRepo = _globals._repositories.address;
        bool connected = _globals._helpers._sqlHelper.TryConnect();
        if(connected)
        {
            bool isRepoOk = SqlRepository<Address>::Check();
            bool ref1Ok_County = CheckRef(Address, countyId, County);
            //bool ref2Ok_County = CheckRef(Address, county2Id, County);
            //bool ref3Ok_County = CheckRef(Address, county3Id, County);

            bool refOk_Country = CheckRef(Address, countryId, Country);

            bool valid = isRepoOk
                         && ref1Ok_County //&& ref2Ok_County && ref3Ok_County
                         && refOk_Country ;
            if(valid)
            {
                DataForm *form = new DataForm(opId);

                QString wCode_title = model->GetOpname();//
                QString title =  _globals._translator.Translate(wCode_title) + ": " + _tr(WCodes::Address);

                form->setWindowTitle(title);

                // referenciákat lekérjük id alapján

                Address data;

                if (model->IsUpdate()) {
                    data = _globals._repositories.address.Get(model->Id());
                    //model->Set_data(data);
                }

                // ez a mezők neveit és azok típusát tartalmazza
                // referencia esetén a value a hivatkozott id,
                QList<MetaValue> m = Address::Meta().ToMetaValues(data);
                form->setMetaValues(m);

                DataRowDefaultModel countyRows = Get_DataRowDefaultModel(Address, countyId, County);
                //DataRowDefaultModel county2Rows = Copy_DataRowDefaultModel(countyRows, Address, county2Id);
                //DataRowDefaultModel county3Rows = Copy_DataRowDefaultModel(countyRows, Address, county3Id);

                DataRowDefaultModel countryRows = Get_DataRowDefaultModel(Address, countryId, Country);

                QList<DataRowDefaultModel> defaults {countyRows, countryRows};//county2Rows, county3Rows,

                    form->SetDataRowDefaults(defaults);

                form->show();

                QObject::connect(form, SIGNAL(AcceptActionTriggered(QUuid)),
                                 a->presenter(), SLOT(process_CreateUpdate_Address_AcceptAction(QUuid)));

                QObject::connect(form, SIGNAL(DoneActionTriggered(QUuid, int)),
                                 a->presenter(), SLOT(process_DoneAction(QUuid, int)));


                model->Set_data(form, data);

            }
        }
    }
}


AddressOperations::Import1Result AddressOperations::Operation_ImportAddress1(Presenter *presenter, IView *sender)
{
    zTrace();
    Import1Result r;
    r.setOpId(Operations::instance().startNew(presenter, sender, __FUNCTION__));

    bool connected = _globals._helpers._sqlHelper.TryConnect();
    if(connected)
    {
        bool isRepoOk = SqlRepository<Address>::Check();
        if(isRepoOk){
            r.setRepoOk(true);
        }
    }
    return r;
}

void AddressOperations::Operation_ImportAddress2(const MainViewModel::FileNameModel& fn)
{
    //MainViewModel::FileNameModel fn = sender->get_CSVFileName_Address();
    QString keyColumnName = FieldName(Address, excelId);
    OperationHelper::Import_private<Address>(fn, keyColumnName,';');
}


