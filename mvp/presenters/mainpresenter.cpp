#include <QFileDialog>
#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStringLiteral>


#include "mainpresenter.h"
#include "helpers/logger.h"
//#include "helpers/sqlhelper.h"
#include "helpers/translator.h"
#include "mvp/viewmodels/mainviewmodel.h"
//#include "dowork.h"
#include "bi/operations.h"
//#include "settings.h"
#include "mvp/views/dataform.h"
//#include "datarowwidget.h"
#include "infrastructure/globals.h"


//#include "helpers/filehelper.h"
#include "helpers/sqlhelper.h"

#include "mvp/models/county.h"
#include "mvp/models/article.h"
#include "mvp/models/solditem.h"
#include "mvp/models/address.h"

#include "mvp/views/datalistform.h"
#include "repositories/sqlrepository.h"

#include "meta/csv_sqlhelper.h"
//#include "meta/sqlmetahelper.h"


extern Globals _globals;

//IMainView* MainPresenter::_logView = nullptr;

MainPresenter::MainPresenter(QObject *parent):Presenter(parent){}

void MainPresenter::appendView(IMainView *w)
{
    if(_views.contains(w)) return;

    // if(_views.length()==0){
    //     _logView = w;
    //     Logger::SetFunction(&MainPresenter::Log);
    // }

    _views.append(w);

    QObject *view_obj = dynamic_cast<QObject *>(w);

    QObject::connect(view_obj, SIGNAL(PushButtonActionTriggered(IMainView *)),
                     this, SLOT(processPushButtonAction(IMainView *)));

    QObject::connect(view_obj, SIGNAL(DBTestActionTriggered(IMainView *)),
                     this, SLOT(processDBTestAction(IMainView *)));

    // UI Form Add tetel
    QObject::connect(view_obj, SIGNAL(Add_SoldItem_ActionTriggered(IMainView *)),
                     this, SLOT(process_Add_SoldItemAction(IMainView *)));

    // UI Form Add Address
    QObject::connect(view_obj, SIGNAL(Add_Address_ActionTriggered(IMainView *)),
                     this, SLOT(process_Add_AddressAction(IMainView *)));

    QObject::connect(view_obj, SIGNAL(Update_Address_ActionTriggered(IMainView *)),
                     this, SLOT(process_Update_AddressAction(IMainView *)));

    // CSV_Import SoldItem - Tetel
    QObject::connect(view_obj, SIGNAL(TetelImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_TetelImport_Action(IMainView *)));

    // CSV_Import Address - Cím
    QObject::connect(view_obj, SIGNAL(CimImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_CimImport_Action(IMainView *)));

    QObject::connect(view_obj, SIGNAL(AddressList_ActionTriggered(IMainView *)),
                     this, SLOT(process_AddressList_Action(IMainView *)));

    //CSV_Import Country - Ország
    QObject::connect(view_obj, SIGNAL(CountryImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_CountryImport_Action(IMainView *)));

    //CSV_Import County - Megye
    QObject::connect(view_obj, SIGNAL(CountyImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_CountyImport_Action(IMainView *)));

    // CSV_Import Partner
    QObject::connect(view_obj, SIGNAL(PartnerImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_PartnerImport_Action(IMainView *)));

    // CSV_Import Article - cikk
    QObject::connect(view_obj, SIGNAL(ArticleImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_ArticleImport_Action(IMainView *)));

    //refreshView(w);
}

void MainPresenter::refreshView(IMainView *w) const { Q_UNUSED(w) };

void MainPresenter::initView(IMainView *w) const {
    MainViewModel::StringModel rm{"1"};
    w->set_DoWorkRModel(rm);

    static const QString conn = QStringLiteral("conn1");
    // SQLHelper::SQLSettings sql_settings{
    //     "QMARIADB",
    //     "biovitality",
    //         {{"192.168.1.105", 3306}},
    //     "zoli",
    //     "Aladar123"
    // };
    //SQLHelper sqlh;

    // bool ok = _globals._helpers._sqlHelper.Connect();

    // if(_globals._helpers._sqlHelper.dbIsValid()){
    //     zInfo("DB "+_globals._settings._sql_settings.dbname+" is valid");
    // } else{
    //     zWarning("DB "+_globals._settings._sql_settings.dbname+" is invalid");
    // }
    w->set_StatusLine({""});
    //_db.close();   

    Repositories::MetaInit();
};



void MainPresenter::processPushButtonAction(IMainView *sender){
    zTrace();
    //auto m = sender->get_DoWorkModel();
    //auto rm = DoWork::Work1(m);
    //sender->set_DoWorkRModel(rm);
}


void MainPresenter::processDBTestAction(IMainView *sender)
{
    zTrace();
    QLocale hu(QLocale::Hungarian);

    zInfo("hu: "+hu.dateFormat());
    QString str = QStringLiteral("2020.04.10.");
    QDate fullfillment = hu.toDate(str);
    zInfo("fullfillment("+str+"): "+fullfillment.toString());

    fullfillment = hu.toDate(str,"yyyy.M.d");
    zInfo("fullfillment("+str+"): "+fullfillment.toString());

    //str = QStringLiteral("2020.04.10.");
    fullfillment = hu.toDate(str,"yyyy.M.d");
    zInfo("fullfillment("+str+"): "+fullfillment.toString());
    /*
    //SqlRepository<SoldItem> sr("SoldItem");
    auto a = sr.Get(2);
    //auto a = sr.GetAll();https://www.facebook.com/
    a.partnerHq = "aaa12";
    a.partnerName = "maki12";
    bool b = sr.Update(a);
    zInfo(QStringLiteral("Update:")+(b?"ok":"failed"));
    a.partnerHq = "aaa118_uj";
    a.partnerName = "maki118_uj";
    bool c = sr.Add(a);
*/
    return;
}

void MainPresenter::Error(const QSqlError& err)
{
    if(err.isValid()) zInfo(QStringLiteral("QSqlError: %1 - %2").arg(err.type()).arg(err.text()));
}

//

void MainPresenter::process_Add_SoldItem_AcceptAction(QUuid opId)
{
    zTrace();
    process_CreateUpdate_AcceptAction<SoldItem>(opId);
}

void MainPresenter::process_CreateUpdate_Address_AcceptAction(QUuid opId)
{
    zTrace();
    process_CreateUpdate_AcceptAction<Address>(opId);
}

void MainPresenter::process_DoneAction(QUuid opId, int r){
    zTrace();
}


template<typename T>
void MainPresenter::process_CreateUpdate_AcceptAction(QUuid opId)
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
                    bool added = repo->Add(data);
                    if(added){

                        if(!parentId.isNull())
                        {
                            // todo 001a kell a row data is átadni, beszúrjuk a rowt a végére
                            emit TableFresh_AddRow(parentId, m.values);
                        }
                    }
                } else if(b->IsUpdate()){
                    bool updated = repo->Update(data);
                    if(updated){
                        //QUuid parentId = Operations::instance().parentId(opId);
                        if(!parentId.isNull()){
                            // todo 001b kell a row data is átadni, felupdateljük a rowt
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

void MainPresenter::process_Add_AddressAction(IMainView *sender){
    zTrace();
    Operation_InsertAddress(sender);
}

void MainPresenter::process_Update_AddressAction(IMainView *sender){
    zTrace();

    Operation_UpdateAddress(sender, QUuid(), 2);
}

void MainPresenter::Operation_UpdateAddress(IMainView *sender, QUuid parent_opId, int id){
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__, parent_opId);

    FormModel<Address>* model = new FormModel<Address>(FormModel_Type::Update, id);
    Operations::instance().setData(opId, model);

    CreateUpdate_Address(opId);
}

void MainPresenter::Operation_InsertAddress(IMainView *sender)
{
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    FormModel<Address>* model = new FormModel<Address>(FormModel_Type::Create, -1);
    Operations::instance().setData(opId, model);

    CreateUpdate_Address(opId);
}

void MainPresenter::CreateUpdate_Address(QUuid opId)
{
    //void *a = Operations::instance().data(opId);
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
                                 this, SLOT(process_CreateUpdate_Address_AcceptAction(QUuid)));

                QObject::connect(form, SIGNAL(DoneActionTriggered(QUuid, int)),
                                 this, SLOT(process_DoneAction(QUuid, int)));


                model->Set_data(form, data);

            }
        }
    }
}

void MainPresenter::process_Add_SoldItemAction(IMainView *sender){
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);


    FormModel<SoldItem>* model = new FormModel<SoldItem>(FormModel_Type::Create, -1);

    //int excelId = 806;

    //int id = _globals._repositories.sr.GetIdBy_ExcelId(excelId);
    //SoldItem data = _globals._repositories.sr.Get(id);

    Operations::instance().setData(opId, model);


    // QString baseTypeName = data.GetBaseTypeName();
    // zInfo("baseTypeName: "+baseTypeName);

    DataForm *form = new DataForm(opId);

    //QString title = _tr(GetWCode(WCodes::AddSoldItem));

    QString title = _tr(WCodes::AddNew)+": "+_tr(WCodes::SoldItem);
    form->setWindowTitle(title);

    SoldItem data;
    //data.partnerName="teszt partner 1";
    //data.county="teszt county 1";
    //model->data = data;
    QList<MetaValue> m = SoldItem::Meta().ToMetaValues(data);
    form->setMetaValues(m);

    // megye defaultjai - county
    // rekordok az sql-ből
    // getall -> rekordok -> model lista



    // partners -> partnerName
    QList<Partner> partners = _globals._repositories.partner.GetAll();
    //DataRowDefaultModel partnerRows = Partner::To_DataRowDefaultModel(partners);
    DataRowDefaultModel partnerRows = Partner::Meta().ToIdMegnevs(partners);
    partnerRows.SetName(SoldItem,partnerName); // ennek a mezőnek lesznek ezek a defaultjai

    // címek -> partnerHq
    QList<Address> addresses = _globals._repositories.address.GetAll();
    //DataRowDefaultModel addressRows = Address::To_DataRowDefaultModel(addresses);
    DataRowDefaultModel addressRows = Address::Meta().ToIdMegnevs(addresses);
    addressRows.SetName(SoldItem,partnerHq); // ennek a mezőnek lesznek ezek a defaultjai

    // megyék - county
    QList<County> counties = _globals._repositories.county.GetAll();
    //DataRowDefaultModel countyRows = County::To_DataRowDefaultModel(counties);
    DataRowDefaultModel countyRows = County::Meta().ToIdMegnevs(counties);
    countyRows.SetName(SoldItem,county); // ennek a mezőnek lesznek ezek a defaultjai

    // cikkek - productName
    QList<Article> articles = _globals._repositories.article.GetAll();
    //DataRowDefaultModel articleRows = Article::To_DataRowDefaultModel(articles);
    DataRowDefaultModel articleRows = Article::Meta().ToIdMegnevs(articles);
    articleRows.SetName(SoldItem,productName); // ennek a mezőnek lesznek ezek a defaultjai

    QList<DataRowDefaultModel> defaults {countyRows,articleRows,addressRows,partnerRows};

    form->SetDataRowDefaults(defaults);

    form->show();
    QObject::connect(form, SIGNAL(AcceptActionTriggered(QUuid)),
                     this, SLOT(process_Add_SoldItem_AcceptAction(QUuid)));

    QObject::connect(form, SIGNAL(DoneActionTriggered(QUuid, int)),
                     this, SLOT(process_DoneAction(QUuid, int)));

}


// import

void MainPresenter::process_CimImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    bool connected = _globals._helpers._sqlHelper.TryConnect();
    if(connected)
    {
        bool isRepoOk = SqlRepository<Address>::Check();
        if(isRepoOk){
            MainViewModel::FileNameModel fn = sender->get_CSVFileName_Address();
            QString keyColumnName = FieldName(Address, excelId);
            Import_private<Address>(fn, keyColumnName,';');
        }
    }
    Operations::instance().stop(opId);
}

void MainPresenter::process_PartnerImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    bool connected = _globals._helpers._sqlHelper.TryConnect();
    if(connected)
    {
        bool isRepoOk = SqlRepository<Partner>::Check();
        if(isRepoOk){
            MainViewModel::FileNameModel fn = sender->get_CSVFileName_Partner();
            QString keyColumnName = FieldName(Partner, excelId);
            Import_private<Partner>(fn, keyColumnName,';');
        }
    }

    Operations::instance().stop(opId);
}

void MainPresenter::process_TetelImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    bool connected = _globals._helpers._sqlHelper.TryConnect();
    if(connected)
    {
        bool isRepoOk = SqlRepository<SoldItem>::Check();
        if(isRepoOk){
            MainViewModel::FileNameModel fn = sender->get_CSVFileName_SoldItem();
            QString keyColumnName = FieldName(SoldItem, excelId);
            Import_private<SoldItem>(fn, keyColumnName,';');
        }
    }
    Operations::instance().stop(opId);
}

void MainPresenter::process_CountyImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    bool connected = _globals._helpers._sqlHelper.TryConnect();
    if(connected)
    {
        bool isRepoOk = SqlRepository<County>::Check();
        if(isRepoOk){
            MainViewModel::FileNameModel fn = sender->get_CSVFileName_County();
            QString keyColumnName = FieldName(County, KSHCode);
            Import_private<County>(fn, keyColumnName,';');
        }
    }
    Operations::instance().stop(opId);
}

void MainPresenter::process_CountryImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    bool connected = _globals._helpers._sqlHelper.TryConnect();
    if(connected)
    {
        bool isRepoOk = SqlRepository<Country>::Check();
        if(isRepoOk){
            MainViewModel::FileNameModel fn = sender->get_CSVFileName_Country();
            QString keyColumnName = FieldName(Country, countryCode);
            Import_private<Country>(fn, keyColumnName,',');
        }
    }
    Operations::instance().stop(opId);
}

// 1. feltételek: legyen adatbázis. legyen tábla. legyenek mezők.
// 1.a: ha nincs konnektálva, konnektáljuk
// 2. legyen file.
// 3. ne nyomjon cancelt

// legyen adatbázis
// 1.

void MainPresenter::process_ArticleImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    //auto repo = _globals._repositories.article;
    bool connected = _globals._helpers._sqlHelper.TryConnect();
    if(connected)
    {
        bool isRepoOk = SqlRepository<Article>::Check();
        if(isRepoOk)
        {
            MainViewModel::FileNameModel fn = sender->get_CSVFileName_Article();
            QString keyColumnName = FieldName(Article, Barcode);
            Import_private<Article>(fn, keyColumnName,';');
        }
    //else
    //{
    //   QString msg = dbErr.ToString();
    //    zWarning(msg);
    //}
    }
    Operations::instance().stop(opId);
}

/*
    bool connected = _globals._helpers._sqlHelper.TryConnect();
    if(connected)
    {
        bool isRepoOk = SqlRepository<Address>::Check();
*/
// template<typename T>
// bool MainPresenter::Import_CheckRepo(SqlRepository<T>& repo){
//     bool connected = _globals._helpers._sqlHelper.TryConnect();
//     if(!connected) return false;

//     SqlRepository<T>::Check(r1->refTypeName());
//     //bool tableExists = repo.isTableExists();
//     //if(!tableExists) return false;
//     //bool fieldsExists = repo.isFieldsExists();
//     //if(!fieldsExists) return false;
//     return true;
// }

template<typename T, typename R>
bool MainPresenter::CheckRef_(const QString& f)
{
    Ref<R>* r1 = T::Meta().template GetRef2<R>(f);
    if(!r1) return false;

    bool ok = SqlRepository<R>::Check();
    return ok;
}

template<typename T, typename R>
DataRowDefaultModel MainPresenter::Get_DataRowDefaultModel_(const QString& f)
{
    //Ref<R>* r1 = T::Meta().template GetRef2<R>();

    QString fieldName = f;// T::Meta().template GetRef_FieldName<R>();
    SqlRepository<R> *repo = SqlRepositoryContainer::Get<R>();

    bool valid = repo && !fieldName.isEmpty();
    if(!valid) return DataRowDefaultModel("");

    QList<R> data = repo->GetAll();
    DataRowDefaultModel rows = R::Meta().ToIdMegnevs(data);
    rows.SetName_(fieldName);
    return rows;
}


template<typename T>
void MainPresenter::Import_private(const MainViewModel::FileNameModel& fn,
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

///
void MainPresenter::process_AddressList_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    ListModel<Address>* model = new ListModel<Address>();
    //model->amType = AddModel_Type::Update;
    Operations::instance().setData(opId, model);

    List_Address(opId);
}

/*
*
*/
void MainPresenter::List_Address(QUuid opId)
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

                QObject::connect(this, SIGNAL(TableFresh_AddRow(QUuid, const  QList<MetaValue>&)),
                                 this, SLOT(process_TableFresh_AddRow(QUuid, const  QList<MetaValue>&)));

                QObject::connect(this, SIGNAL(TableFresh_UpdateRow(QUuid, const  QList<MetaValue>&)),
                                 this, SLOT(process_TableFresh_UpdateRow(QUuid, const  QList<MetaValue>&)));

                QObject::connect(form, SIGNAL(DoneActionTriggered(QUuid, int)),
                                 this, SLOT(process_DoneAction2(QUuid, int)));

                model->Set_data(form, data);

            }
        }
    }
}


void MainPresenter::process_DoneAction2(QUuid opId, int r){
    zTrace();

    QObject::disconnect(this, SIGNAL(TableFresh()),
                     this, SLOT(process_TableFresh()));


    Operations::instance().stop(opId);
}



void MainPresenter::process_UpdateAction(QUuid opId, int id)
{
    zTrace();

    //void *a = Operations::instance().data(opId);
    //ListModel<Address> *model = reinterpret_cast<ListModel<Address>*>(a);
    //if(model)
   // {
        Operation_UpdateAddress(_views.at(0), opId, id);
    //}

}

void MainPresenter::process_InsertAction(QUuid opid)
{
    zTrace();
    Operation_InsertAddress(_views.at(0));

    // be kell frissíteni a táblában az új rekordot
}

void MainPresenter::process_TableFresh_AddRow(QUuid opid, const QList<MetaValue>& values)
{
    //zTrace();
    DataListForm *d = Operations::instance().data<DataListForm>(opid);
    if(d){
        d->AddRow(values);
    }
}

void MainPresenter::process_TableFresh_UpdateRow(QUuid opid, const QList<MetaValue>& values)
{
    //zTrace();
    DataListForm *d = Operations::instance().data<DataListForm>(opid);
    if(d){
        d->UpdateRow(values);
    }
}

