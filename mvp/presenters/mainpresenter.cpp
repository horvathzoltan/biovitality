#include "mainpresenter.h"
#include "helpers/logger.h"
//#include "helpers/sqlhelper.h"
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

    zInfo("hu:"+hu.dateFormat());
    QString str = QStringLiteral("2020.04.10.");
    QDate fullfillment = hu.toDate(str);
    zInfo("fullfillment("+str+"):"+fullfillment.toString());

    fullfillment = hu.toDate(str,"yyyy.M.d");
    zInfo("fullfillment("+str+"):"+fullfillment.toString());

    //str = QStringLiteral("2020.04.10.");
    fullfillment = hu.toDate(str,"yyyy.M.d");
    zInfo("fullfillment("+str+"):"+fullfillment.toString());
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

// void MainPresenter::Error2(DbErr err)
// {
//     if(!err.isDbValid){
//         zWarning("db:"+err._dbName+" is invalid");
//     }else if(!err.isTableExists){
//         zWarning("table:"+err._dbName+"."+err._tableName+" is not exists");
//     }
// }

void MainPresenter::process_Add_AddressAction(IMainView *sender){
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    auto addressRepo = _globals._repositories.address;
    bool isRepoOk = Import_CheckRepo(addressRepo);

    QVariantList rl = Address::GetRefs();

    for (QVariant &v : rl) {
        //RepositoryBase *r = RepositoryBase::GetRepository(refName);
        //void *d = v.data();
        //RefBase *r = (RefBase *)d;
        RefBase r = v.value<RefBase>();
        if (r.refTypeName() == "County") {
            //QVariant a = r;

            // decltype(r->m.metaType().) at ;
            // Ref<County>* r2 = reinterpret_cast<Ref<County>*>(r);

            bool tableExists = SqlRepository<County>::Check(r.refTypeName());
            // County c = *(r2->metaInstance());
            // RepositoryBase* rx =
            // RepositoryBase::GetRepository(r->refTypeName());
            // SqlRepository<decltype(c)>* repo =
            //     reinterpret_cast<SqlRepository<decltype(c)>* >(rx);
            // bool tableExists = repo->isTableExists();
            zInfo(QStringLiteral("tableExists") +
                  (tableExists ? "ok" : "failed"));
        }
    }

    // meg kell nézni a hivatkozott modellek repoit is

    bool valid = isRepoOk;
    if(valid)
    {
        AddModel<Address>* model = new AddModel<Address>();

        Operations::instance().setData(opId, model);

        model->dataForm = new DataForm(opId);

        Address data = _globals._repositories.address.Get(2);
        model->data = data;
        QList<MetaValue> m = data.GetMetaValues();
        model->dataForm->setMetaValues(m);

        model->dataForm->show();
    }
    Operations::instance().stop(opId);
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
    // zInfo("baseTypeName:"+baseTypeName);

    model->dataForm = new DataForm(opId);

    QString title = _tr(GetWCode(WCodes::AddSoldItem));
    model->dataForm->setWindowTitle(title);

    SoldItem data;
    //data.partnerName="teszt partner 1";
    //data.county="teszt county 1";
    model->data = data;
    QList<MetaValue> m = data.GetMetaValues();
    model->dataForm->setMetaValues(m);

    // megye defaultjai - county
    // rekordok az sql-ből
    // getall -> rekordok -> model lista

    // partners -> partnerName
    QList<Partner> partners = _globals._repositories.partner.GetAll();
    DataRowDefaultModel partnerRows = Partner::To_DataRowDefaultModel(partners);
    partnerRows.name = "partnerName"; // ennek a mezőnek lesznek ezek a defaultjai

    // címek -> partnerHq
    QList<Address> addresses = _globals._repositories.address.GetAll();
    DataRowDefaultModel addressRows = Address::To_DataRowDefaultModel(addresses);
    addressRows.name = "partnerHq"; // ennek a mezőnek lesznek ezek a defaultjai

    // megyék - county
    QList<County> counties = _globals._repositories.county.GetAll();
    DataRowDefaultModel countyRows = County::To_DataRowDefaultModel(counties);
    countyRows.name = "county"; // ennek a mezőnek lesznek ezek a defaultjai

    // cikkek - productName
    QList<Article> articles = _globals._repositories.article.GetAll();
    DataRowDefaultModel articleRows = Article::To_DataRowDefaultModel(articles);
    articleRows.name = "productName"; // ennek a mezőnek lesznek ezek a defaultjai

    QList<DataRowDefaultModel> defaults {countyRows,articleRows,addressRows,partnerRows};

    model->dataForm->SetDataRowDefaults(defaults);

    model->dataForm->show();
    QObject::connect(model->dataForm, SIGNAL(AcceptActionTriggered(QUuid)),
                     this, SLOT(process_Add_SoldItem_AcceptAction(QUuid)));

}

void MainPresenter::process_Add_SoldItem_AcceptAction(QUuid opId)
{
    zInfo("processAcceptAction");

    OperationModel *a = Operations::instance().data(opId);
    AddModel<SoldItem> *b = reinterpret_cast<AddModel<SoldItem>*>(a);

    if(b){
        DataModel m = b->dataForm->metaValues();
        if(m.isValid()){
            b->dataForm->done(1);
            // itt van az hogy le kéne a változtatott rekordot menteni
            SoldItem data = SoldItem::FromMetaValues(m.values);
            _globals._repositories.solditem.Add(data);
        }
        else{
            b->dataForm->SetValidations(m.validations);
        }
    }

}

// import

void MainPresenter::process_CimImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    SqlRepository<Address> repo = _globals._repositories.address;
    bool isRepoOk = Import_CheckRepo(repo);

    bool valid = isRepoOk;
    if(valid){
        MainViewModel::FileNameModel fn = sender->get_CSVFileName_Address();
        QString keyColumnName = FieldName(Address, excelId);
        Import_private(fn, repo, keyColumnName,';');
    }

    Operations::instance().stop(opId);
}

void MainPresenter::process_PartnerImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    SqlRepository<Partner> repo = _globals._repositories.partner;
    bool isRepoOk = Import_CheckRepo(repo);

    bool valid = isRepoOk;
    if(valid){
        MainViewModel::FileNameModel fn = sender->get_CSVFileName_Partner();
        QString keyColumnName = FieldName(Partner, excelId);
        Import_private(fn, repo,keyColumnName,';');
    }

    Operations::instance().stop(opId);
}

void MainPresenter::process_TetelImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    SqlRepository<SoldItem> repo = _globals._repositories.solditem;
    bool isRepoOk = Import_CheckRepo(repo);

    bool valid = isRepoOk;
    if(valid){
        MainViewModel::FileNameModel fn = sender->get_CSVFileName_SoldItem();
        QString keyColumnName = FieldName(SoldItem, excelId);
        Import_private(fn, repo, keyColumnName,';');
    }

    Operations::instance().stop(opId);
}

void MainPresenter::process_CountyImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    SqlRepository<County> repo = _globals._repositories.county;
    bool isRepoOk = Import_CheckRepo(repo);

    bool valid = isRepoOk;
    if(valid){
        MainViewModel::FileNameModel fn = sender->get_CSVFileName_County();
        QString keyColumnName = FieldName(County, KSHCode);
        Import_private(fn,  repo, keyColumnName,';');
    }

    Operations::instance().stop(opId);
}

void MainPresenter::process_CountryImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    SqlRepository<Country> repo = _globals._repositories.country;
    bool isRepoOk = Import_CheckRepo(repo);

    bool valid = isRepoOk;
    if(valid){
        MainViewModel::FileNameModel fn = sender->get_CSVFileName_Country();
        QString keyColumnName = FieldName(Country, countryCode);
        Import_private(fn, repo, keyColumnName,',');
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

    auto repo = _globals._repositories.article;
    bool isRepoOk = Import_CheckRepo(repo);

    bool valid = isRepoOk;
    if(valid){
        MainViewModel::FileNameModel fn = sender->get_CSVFileName_Article();
        QString keyColumnName = FieldName(Article, Barcode);
        Import_private(fn, repo, keyColumnName,';');
    }
    //else
    //{
    //   QString msg = dbErr.ToString();
    //    zWarning(msg);
    //}

    Operations::instance().stop(opId);
}

template<typename T>
bool MainPresenter::Import_CheckRepo(SqlRepository<T>& repo){
    bool connected = _globals._helpers._sqlHelper.TryConnect();
    if(!connected) return false;
    bool tableExists = repo.isTableExists();
    if(!tableExists) return false;
    return true;
}

template<typename T>
void MainPresenter::Import_private(const MainViewModel::FileNameModel& fn,
                                   SqlRepository<T>& repo,
                                   const QString& keyColumnName,
                                   const QChar& separator)
{    
        if(!fn.isCanceled){
            CSV_SQLHelper::Import(fn.fileName, repo, keyColumnName, separator);
        } else{
            zInfo("cancelled");
        }   
}
