#include "mainpresenter.h"
#include "helpers/logger.h"
#include "helpers/sqlhelper.h"
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

    auto *view_obj = dynamic_cast<QObject*>(w);

    QObject::connect(view_obj, SIGNAL(PushButtonActionTriggered(IMainView *)),
                     this, SLOT(processPushButtonAction(IMainView *)));

    QObject::connect(view_obj, SIGNAL(DBTestActionTriggered(IMainView *)),
                     this, SLOT(processDBTestAction(IMainView *)));

    // Add tetel
    QObject::connect(view_obj, SIGNAL(AddSoldItemActionTriggered(IMainView *)),
                     this, SLOT(process_Add_SoldItemAction(IMainView *)));

    // CSV_Imoort tetel
    QObject::connect(view_obj, SIGNAL(TetelImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_TetelImport_Action(IMainView *)));

    // CSV_Import Cím
    QObject::connect(view_obj, SIGNAL(CimImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_CimImport_Action(IMainView *)));

    // CSV_Import Partner
    QObject::connect(view_obj, SIGNAL(PartnerImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_PartnerImport_Action(IMainView *)));

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
    _globals._helpers._sqlHelper.Init(_globals._settings._sql_settings);
    bool ok = _globals._helpers._sqlHelper.Connect();

    if(_globals._helpers._sqlHelper.dbIsValid()){        
        zInfo("DB "+_globals._settings._sql_settings.dbname+" is valid");
    } else{
        zWarning("DB "+_globals._settings._sql_settings.dbname+" is invalid");
    }
    w->set_StatusLine({""});
    //_db.close();

    SoldItem::SetMetaVerbose(false);
    Article::SetMetaVerbose(false);
    County::SetMetaVerbose(false);
    //Address::SetMetaVerbose(false);

    Repositories::MetaInit();
};



void MainPresenter::processPushButtonAction(IMainView *sender){
    zTrace();
    //auto m = sender->get_DoWorkModel();
    //auto rm = DoWork::Work1(m);
    //sender->set_DoWorkRModel(rm);
}

void MainPresenter::process_TetelImport_Action(IMainView *sender)
{
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);
    SqlRepository<SoldItem>& repo = _globals._repositories.solditem;

    DbErr err;
    err.isDbValid = _globals._helpers._sqlHelper.dbIsValid();
    err.isTableExists = repo.isTableExists();

    CSVErrModel csverr;

    if(err.isValid()){
        MainViewModel::FileNameModel fn = sender->get_TetelCSVFileName();
        if(!fn.isCanceled)
        {
            FileHelper::CSVModel csvModel = FileHelper::LoadCSV(fn.fileName);
            if(csvModel.error == FileHelper::Ok){
                zInfo("file ok");
                QList<SoldItem> items = SoldItem::CSV_Import(csvModel.records);
                csverr.itemsCount = items.count();

                zInfo("items loaded: "+csverr.ToSting());
                RepoUpdate(repo, items);

                // megvan a modell lista, egyenként meg kell nézni excel_id szerint, hogy
                // ha létezik, update
                // ha nem, insert
                // todo 001 storno flag
                // todo 002 partner törzs - partner id bevezetése
                // - 1. partner import
                // - 2. tétel import
                //SoldItemRepository::InsertOrUpdate(items);

                // if(!items.isEmpty())
                // {
                //     int i_all=0, u_all=0;
                //     int i_ok=0, u_ok=0;
                //     for(auto&i:items){
                //         bool contains = _globals._repositories.solditem.ContainsBy_ExcelId(i.excelId);
                //         if(contains){
                //             int id =  _globals._repositories.solditem.GetIdBy_ExcelId(i.excelId); // meg kell szerezni az id-t
                //             if(id!=-1)
                //             {
                //                 i.id = id;
                //                 u_all++;
                //                 bool ok =  _globals._repositories.solditem.Update(i);
                //                 if(ok) u_ok++;
                //             } else{
                //                 zInfo("no id for excelId: "+QString::number(i.excelId));
                //             }
                //         } else{
                //             i_all++;
                //             bool ok =  _globals._repositories.solditem.Add(i);
                //             if(ok) i_ok++;
                //         }
                //     }
                //     zInfo(QStringLiteral("Updated: %1/%2").arg(u_ok).arg(u_all));
                //     zInfo(QStringLiteral("Inserted: %1/%2").arg(i_ok).arg(i_all));
                // } else{
                //     zInfo("no items to import");
                // }
            }
            else
            {
                zWarning("items load failed: "+csverr.ToSting());
            }
        }
        else
        {
            zInfo("cancelled");
        }
    }
    else
    {
        zWarning("db is invalid");
    }
    Operations::instance().stop(opId);
}

void MainPresenter::processDBTestAction(IMainView *sender)
{
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

void MainPresenter::Error2(DbErr err)
{
    if(!err.isDbValid){
        zWarning("db is invalid");
    }else if(!err.isTableExists){
        zWarning("address table is not exists");
    }
}

void MainPresenter::process_Add_SoldItemAction(IMainView *sender){
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);


    AddSoldItemModel* model = new AddSoldItemModel();

    //int excelId = 806;

    //int id = _globals._repositories.sr.GetIdBy_ExcelId(excelId);
    //SoldItem data = _globals._repositories.sr.Get(id);

    SoldItem data;
    data.partnerName="teszt partner 1";
    data.county="teszt county 1";
    model->data = data;

    Operations::instance().setData(opId, model);

    QList<MetaValue> m = data.GetMetaValues();

    // QString baseTypeName = data.GetBaseTypeName();
    // zInfo("baseTypeName:"+baseTypeName);

    model->dataForm = new DataForm(opId);

    QString title = _tr(GetWCode(WCodes::AddSoldItem));
    model->dataForm->setWindowTitle(title);
    model->dataForm->setMetaValues(m);

    // a county defaultjai:
    // rekordok az sql-ből
    QList<County> counties = _globals._repositories.county.GetAll();
    // rekordok -> model lista
    DataRowDefaultModel cd = County::To_DataRowDefaultModel(counties);
    cd.name = QT_STRINGIFY(county); // ennek a mezőnek lesznek ezek a defaultjai
    //QList<DataRowDefaultModel> d {{cd}};
    //model->dataForm->SetDataRowDefaults(d);


    QList<Article> articles = _globals._repositories.article.GetAll();
    // rekordok -> model lista
    DataRowDefaultModel ad = Article::To_DataRowDefaultModel(articles);
    ad.name = QT_STRINGIFY(productName); // ennek a mezőnek lesznek ezek a defaultjai

    QList<DataRowDefaultModel> da {cd,ad};

    model->dataForm->SetDataRowDefaults(da);

    model->dataForm->show();
    QObject::connect(model->dataForm, SIGNAL(AcceptActionTriggered(QUuid)),
                     this, SLOT(process_Add_SoldItem_AcceptAction(QUuid)));


   // zInfo("platty");
}

void MainPresenter::process_Add_SoldItem_AcceptAction(QUuid opId)
{
    zInfo("processAcceptAction");

    OperationModel *a = Operations::instance().data(opId);
    AddSoldItemModel *b = reinterpret_cast<AddSoldItemModel*>(a);        

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

//

void MainPresenter::process_CimImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);
    SqlRepository<Address>& repo =  _globals._repositories.address;

    DbErr err;
    err.isDbValid = _globals._helpers._sqlHelper.dbIsValid();
    err.isTableExists = repo.isTableExists();

    CSVErrModel csverr;

    //zInfo(QStringLiteral("isTableExists:")+((isTableExists)?"ok":"false"));
    if(err.isValid()){
        MainViewModel::FileNameModel fn = sender->get_CimCSVFileName();
        if(!fn.isCanceled)
        {
            FileHelper::CSVModel csvModel = FileHelper::LoadCSV(fn.fileName);
            if(csvModel.error == FileHelper::Ok)
            {
                zInfo("file ok");
                QList<Address> items = Address::CSV_Import(csvModel.records);
                csverr.itemsCount = items.count();

                zInfo("items loaded: "+csverr.ToSting());
                RepoUpdate(repo, items);
                // megvan a modell lista, egyenként meg kell nézni excel_id szerint, hogy
                // ha létezik, update
                // ha nem, insert
                // todo 001 storno flag
                // todo 002 partner törzs - partner id bevezetése
                // - 1. partner import
                // - 2. tétel import
                //SoldItemRepository::InsertOrUpdate(items);

                // SqlRepository<Address>& repo =  _globals._repositories.address;

                // if(!items.isEmpty())
                // {
                //     int i_all=0, u_all=0;
                //     int i_ok=0, u_ok=0;
                //     for(auto&i:items){
                //         bool contains = repo.ContainsBy_ExcelId(i.excelId);
                //         if(contains){
                //             int id =  repo.GetIdBy_ExcelId(i.excelId); // meg kell szerezni az id-t
                //             if(id!=-1)
                //             {
                //                 i.id = id;
                //                 u_all++;
                //                 bool ok =  repo.Update(i);
                //                 if(ok) u_ok++;
                //             } else{
                //                 zInfo("no id for excelId: "+QString::number(i.excelId));
                //             }
                //         } else{
                //             i_all++;
                //             bool ok =  repo.Add(i);
                //             if(ok) i_ok++;
                //         }
                //     }
                //     zInfo(QStringLiteral("Updated: %1/%2").arg(u_ok).arg(u_all));
                //     zInfo(QStringLiteral("Inserted: %1/%2").arg(i_ok).arg(i_all));
                // } else{
                //     zInfo("no items to import");
                // }
            }
            else
            {
                zWarning("items load failed: "+csverr.ToSting());
            }
        }
        else
        {
            zInfo("cancelled");
        }
    }
    else
    {
        Error2(err);
    }
    Operations::instance().stop(opId);
}

void MainPresenter::process_PartnerImport_Action(IMainView *sender)
{
    zTrace();
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);
    SqlRepository<Partner>& repo = _globals._repositories.partner;

    DbErr err;
    err.isDbValid = _globals._helpers._sqlHelper.dbIsValid();
    err.isTableExists = repo.isTableExists();

    CSVErrModel csverr;

    if(err.isValid()){
        MainViewModel::FileNameModel fn = sender->get_PartnerCSVFileName();
        if(!fn.isCanceled)
        {
            FileHelper::CSVModel csvModel = FileHelper::LoadCSV(fn.fileName);

            csverr.fileName = fn.fileName;
            csverr.recordsCount = csvModel.records.count();

            if(csvModel.error == FileHelper::Ok){
                QList<Partner> items = Partner::CSV_Import(csvModel.records);
                csverr.itemsCount = items.count();

                zInfo("items loaded: "+csverr.ToSting());
                RepoUpdate(repo, items);
            }
            else
            {
                zWarning("items load failed: "+csverr.ToSting());
            }
        }
        else
        {
            zInfo("cancelled");
        }
    }
    else
    {
        Error2(err);
    }
    Operations::instance().stop(opId);
}


// megvan a modell lista, egyenként meg kell nézni excel_id szerint, hogy
// ha létezik, update
// ha nem, insert
// todo 001 storno flag
// todo 002 partner törzs - partner id bevezetése
// - 1. partner import
// - 2. tétel import
//SoldItemRepository::InsertOrUpdate(items);

template<typename T>
void MainPresenter::RepoUpdate(SqlRepository<T> repo, QList<T> items)
{
    if(items.isEmpty()){
        zInfo("no items to import");
        return;
    }

    int i_all=0, u_all=0;
    int i_ok=0, u_ok=0;
    for(auto&i:items){
        bool contains = repo.ContainsBy_ExcelId(i.excelId);
        if(contains){
            int id =  repo.GetIdBy_ExcelId(i.excelId); // meg kell szerezni az id-t
            if(id!=-1)
            {
                i.id = id;
                u_all++;
                bool ok =  repo.Update(i);
                if(ok) u_ok++;
            } else{
                zInfo("no id for excelId: "+QString::number(i.excelId));
            }
        } else{
            i_all++;
            bool ok =  repo.Add(i);
            if(ok) i_ok++;
        }
    }

    zInfo(QStringLiteral("Updated: %1/%2").arg(u_ok).arg(u_all));
    zInfo(QStringLiteral("Inserted: %1/%2").arg(i_ok).arg(i_all));
}
