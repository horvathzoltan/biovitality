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

#include <QFileDialog>
#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStringLiteral>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <mvp/models/county.h>
#include <mvp/models/article.h>
#include <mvp/models/solditem.h>
#include <mvp/models/address.h>

#include <repositories/sqlrepository.h>

#include <meta/csv_sqlhelper.h>
#include <meta/sqlmetahelper.h>


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

    // CSV_Import SoldItem - Tetel
    QObject::connect(view_obj, SIGNAL(TetelImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_TetelImport_Action(IMainView *)));

    // CSV_Import Address - Cím
    QObject::connect(view_obj, SIGNAL(CimImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_CimImport_Action(IMainView *)));

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
    process_Add_AcceptAction<SoldItem>(opId);
}

void MainPresenter::process_Add_Address_AcceptAction(QUuid opId)
{
    zTrace();
    process_Add_AcceptAction<Address>(opId);
}

void MainPresenter::process_DoneAction(QUuid opId, int r){
    zTrace();
    Operations::instance().stop(opId);
}


template<typename T>
void MainPresenter::process_Add_AcceptAction(QUuid opId)
{
    zTrace();

    OperationModel *a = Operations::instance().data(opId);
    AddModel<T> *b = reinterpret_cast<AddModel<T>*>(a);

    if(b){
        DataModel m = b->dataForm->metaValues();
        if(m.isValid()){
            b->dataForm->done(1);
            // itt van az hogy le kéne a változtatott rekordot menteni
            T data = T::Meta().FromMetaValues(m.values);

            SqlRepository<T> *repo = //_globals._repositories.address;
                SqlRepositoryContainer::Get<T>();

            if(repo)
            {
                repo->Add(data);
            }
        }
        else{
            b->dataForm->SetValidations(m.validations);
        }
    }

    //Operations::instance().stop(opId);
}

void MainPresenter::process_Add_AddressAction(IMainView *sender){
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    auto addressRepo = _globals._repositories.address;
    bool connected = _globals._helpers._sqlHelper.TryConnect();
    if(connected)
    {
        bool isRepoOk = SqlRepository<Address>::Check();
        bool ref1Ok_County = CheckRef(Address, countyId, County);
        bool ref2Ok_County = CheckRef(Address, county2Id, County);
        bool ref3Ok_County = CheckRef(Address, county3Id, County);

        bool refOk_Country = CheckRef(Address, countryId, Country);

        bool valid = isRepoOk
                     && ref1Ok_County && ref2Ok_County && ref3Ok_County
                     && refOk_Country ;
        if(valid)
        {
            AddModel<Address>* model = new AddModel<Address>();

            Operations::instance().setData(opId, model);

            model->dataForm = new DataForm(opId);

            //QString title = _tr(GetWCode(WCodes::AddSoldItem));
            QString title = _tr(WCodes::AddAddress);
            model->dataForm->setWindowTitle(title);

            //referenciákat lekérjük id alapján
            Address data = _globals._repositories.address.Get(2);
            model->data = data;
            QList<MetaValue> m = Address::Meta().ToMetaValues(&data);
            model->dataForm->setMetaValues(m);

            DataRowDefaultModel countyRows = Get_DataRowDefaultModel(Address, countyId, County);
            DataRowDefaultModel county2Rows = Get_DataRowDefaultModel(Address, county2Id, County);
            DataRowDefaultModel county3Rows = Get_DataRowDefaultModel(Address, county3Id, County);

            DataRowDefaultModel countryRows = Get_DataRowDefaultModel(Address, countryId, Country);

            QList<DataRowDefaultModel> defaults {countyRows, county2Rows, county3Rows, countryRows};

            model->dataForm->SetDataRowDefaults(defaults);

            model->dataForm->show();

            QObject::connect(model->dataForm, SIGNAL(AcceptActionTriggered(QUuid)),
                              this, SLOT(process_Add_Address_AcceptAction(QUuid)));

            QObject::connect(model->dataForm, SIGNAL(DoneActionTriggered(QUuid, int)),
                             this, SLOT(process_DoneAction(QUuid, int)));
        }
    }    
}




void MainPresenter::process_Add_SoldItemAction(IMainView *sender){
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);


    AddModel<SoldItem>* model = new AddModel<SoldItem>();

    //int excelId = 806;

    //int id = _globals._repositories.sr.GetIdBy_ExcelId(excelId);
    //SoldItem data = _globals._repositories.sr.Get(id);

    Operations::instance().setData(opId, model);



    // QString baseTypeName = data.GetBaseTypeName();
    // zInfo("baseTypeName: "+baseTypeName);

    model->dataForm = new DataForm(opId);

    //QString title = _tr(GetWCode(WCodes::AddSoldItem));
    QString title = _tr(WCodes::AddSoldItem);
    model->dataForm->setWindowTitle(title);

    SoldItem data;
    //data.partnerName="teszt partner 1";
    //data.county="teszt county 1";
    model->data = data;
    QList<MetaValue> m = SoldItem::Meta().ToMetaValues(&data);
    model->dataForm->setMetaValues(m);

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

    model->dataForm->SetDataRowDefaults(defaults);

    model->dataForm->show();
    QObject::connect(model->dataForm, SIGNAL(AcceptActionTriggered(QUuid)),
                     this, SLOT(process_Add_SoldItem_AcceptAction(QUuid)));

    QObject::connect(model->dataForm, SIGNAL(DoneActionTriggered(QUuid, int)),
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
