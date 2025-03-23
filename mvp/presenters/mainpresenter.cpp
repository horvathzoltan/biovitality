#include <QFileDialog>
#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStringLiteral>

#include "infrastructure/globals.h"
#include "repositories/sqlrepository.h"
#include "meta/csv_sqlhelper.h"

//#include "bi/address/addresslist.h"
//#include "bi/address/addresslist.h"
//#include "bi/address/addressoperations.h"
#include "bi/operations.h"
#include "bi/operationhelper.h"

#include "mainpresenter.h"
#include "mainpresenter_address.h"
#include "helpers/logger.h"
#include "helpers/translator.h"
#include "helpers/sqlhelper.h"

#include "mvp/models/county.h"
#include "mvp/models/article.h"
#include "mvp/models/solditem.h"
#include "mvp/models/address.h"
#include "mvp/viewmodels/mainviewmodel.h"
#include "mvp/views/dataform.h"


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

    _mainPresenter_Address.Connect(view_obj);

    QObject::connect(view_obj, SIGNAL(PushButtonActionTriggered(IMainView *)),
                     this, SLOT(processPushButtonAction(IMainView *)));

    QObject::connect(view_obj, SIGNAL(DBTestActionTriggered(IMainView *)),
                     this, SLOT(processDBTestAction(IMainView *)));

    // UI Form Add tetel
    QObject::connect(view_obj, SIGNAL(Add_SoldItem_ActionTriggered(IMainView *)),
                     this, SLOT(process_Add_SoldItemAction(IMainView *)));   

    // CSV_Import SoldItem - Tetel
    QObject::connect(view_obj, SIGNAL(TetelImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_TetelImport_Action(IMainView *)));


    // Partner List
    QObject::connect(view_obj, SIGNAL(PartnerList_ActionTriggered(IMainView *)),
                     this, SLOT(process_PartnerList_Action(IMainView *)));

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
    w->set_StatusLine({""});

    Repositories::MetaInit();
};



void MainPresenter::processPushButtonAction(IMainView *sender){
    zTrace();
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

    fullfillment = hu.toDate(str,"yyyy.M.d");
    zInfo("fullfillment("+str+"): "+fullfillment.toString());
    return;
}

// void MainPresenter::Error(const QSqlError& err)
// {
//     if(err.isValid()) zInfo(QStringLiteral("QSqlError: %1 - %2").arg(err.type()).arg(err.text()));
// }

//

void MainPresenter::process_Add_SoldItem_AcceptAction(QUuid opId)
{
    zTrace();
    auto e = OperationHelper::process_CreateUpdate_AcceptAction<SoldItem>(opId);
    // if(e.type==OperationHelper::AcceptActionType::AddRow){
    //     zInfo("AddRow");
    //     emit  TableFresh_AddRow(e.parentId, e.m_values);
    // } else if(e.type==OperationHelper::AcceptActionType::UpdateRow){
    //     zInfo("UpdateRow");
    //     emit  TableFresh_UpdateRow(e.parentId, e.m_values);
    // }
}



void MainPresenter::process_DoneAction(QUuid opId, int r){
    zTrace();
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
    DataRowDefaultModel partnerRows = Partner::Meta().ToIdMegnevs(partners);
    partnerRows.SetName(SoldItem,partnerName); // ennek a mezőnek lesznek ezek a defaultjai

    // címek -> partnerHq
    QList<Address> addresses = _globals._repositories.address.GetAll();
    DataRowDefaultModel addressRows = Address::Meta().ToIdMegnevs(addresses);
    addressRows.SetName(SoldItem,partnerHq); // ennek a mezőnek lesznek ezek a defaultjai

    // megyék - county
    QList<County> counties = _globals._repositories.county.GetAll();
    DataRowDefaultModel countyRows = County::Meta().ToIdMegnevs(counties);
    countyRows.SetName(SoldItem,county); // ennek a mezőnek lesznek ezek a defaultjai

    // cikkek - productName
    QList<Article> articles = _globals._repositories.article.GetAll();
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

//

void MainPresenter::process_PartnerList_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    ListModel<Partner>* model = new ListModel<Partner>();
    //model->amType = AddModel_Type::Update;
    Operations::instance().setData(opId, model);

    //List_Partner(opId);
}


// /*ADDRESS*/

// // Create
// void MainPresenter::process_Add_AddressAction(IMainView *sender){
//     zTrace();
//     AddressOperations::Operation_InsertAddress(this, sender);
// }

// // Update
// void MainPresenter::process_Update_AddressAction(IMainView *sender){
//     zTrace();

//     AddressOperations::Operation_UpdateAddress(this, sender, QUuid(), 2);
// }

// // ReadAll
// void MainPresenter::process_AddressList_Action(IMainView *sender)
// {
//     zTrace();
//     QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

//     ListModel<Address>* model = new ListModel<Address>();

//     AddressList *adl = new AddressList();

//     model->setAddressList(adl);

//     //model->amType = AddModel_Type::Update;
//     Operations::instance().setData(opId, model);

//     adl->List_Address(opId, this);
// }

// // Create/Update
// void MainPresenter::process_CreateUpdate_Address_AcceptAction(QUuid opId)
// {
//     zTrace();
//     auto e = OperationHelper::process_CreateUpdate_AcceptAction<Address>(opId);
//     if(e.type!=OperationHelper::AcceptActionType::None)
//     {
//         ListModel<Address> *model = Operations::instance().data<ListModel<Address>> (e.parentId);
//         if(model)
//         {
//             DataListForm *form = model->dataListForm();
//             if(form)
//             {
//                 if(e.type==OperationHelper::AcceptActionType::AddRow){
//                     emit  form->TableFresh_AddRow(e.parentId, e.m_values);
//                 } else if(e.type==OperationHelper::AcceptActionType::UpdateRow){
//                     emit  form->TableFresh_UpdateRow(e.parentId, e.m_values);
//                 }
//             }
//         }
//     }
// }

// // Import

// void MainPresenter::process_CimImport_Action(IMainView *sender)
// {
//     zTrace();
//     AddressOperations::Import1Result a = AddressOperations::Operation_ImportAddress1(this, sender);

//     if(a.isValid())
//     {
//         MainViewModel::FileNameModel fn = sender->get_CSVFileName_Address();
//         if(fn.IsValid())
//         {
//             AddressOperations::Operation_ImportAddress2(fn);
//         }
//     }
//     Operations::instance().stop(a.opId());
// }





