#include "mainpresenter.h"
#include "helpers/logger.h"
#include "helpers/sqlhelper.h"
#include "mainviewmodel.h"
#include "dowork.h"
#include "operations.h"
//#include "settings.h"
#include "dataform.h"
//#include "datarowwidget.h"
#include "globals.h"

#include <QFileDialog>
#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include <QStringLiteral>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <bi/models/article.h>
#include <bi/models/county.h>
#include <bi/models/article.h>
#include <bi/models/solditem.h>
#include <bi/models/address.h>

#include <bi/repositories/sqlrepository.h>

#include <bi/helpers/sqlmetahelper.h>


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

    QObject::connect(view_obj, SIGNAL(AddSoldItemActionTriggered(IMainView *)),
                     this, SLOT(processSoldItemAction(IMainView *)));

    // CSV_Imoort tetel
    QObject::connect(view_obj, SIGNAL(TetelImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_TetelImport_Action(IMainView *)));

    // CSV_Import Cím
    QObject::connect(view_obj, SIGNAL(CimImport_ActionTriggered(IMainView *)),
                     this, SLOT(process_CimImport_Action(IMainView *)));

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

    Repositories::MetaInit();
};



void MainPresenter::processPushButtonAction(IMainView *sender){
    zTrace();
    auto m = sender->get_DoWorkModel();
    auto rm = DoWork::Work1(m);
    sender->set_DoWorkRModel(rm);
}

void MainPresenter::process_TetelImport_Action(IMainView *sender)
{
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

    MainViewModel::StringModel fn = sender->get_TetelCSVFileName();

    FileHelper::CSVModel csvModel = FileHelper::LoadCSV(fn.str);
    if(csvModel.error == FileHelper::Ok){
        zInfo("file ok");
        QList<SoldItem> items = SoldItem::CSV_Import(csvModel.records);

        // megvan a modell lista, egyenként meg kell nézni excel_id szerint, hogy
        // ha létezik, update
        // ha nem, insert
        // todo 001 storno flag
        // todo 002 partner törzs - partner id bevezetése
        // - 1. partner import
        // - 2. tétel import
        //SoldItemRepository::InsertOrUpdate(items);
        if(!items.isEmpty())
        {
            int i_all=0, u_all=0;
            int i_ok=0, u_ok=0;
            for(auto&i:items){
                bool contains = _globals._repositories.sr.ContainsBy_ExcelId(i.excelId);
                if(contains){
                    int id =  _globals._repositories.sr.GetIdBy_ExcelId(i.excelId); // meg kell szerezni az id-t
                    if(id!=-1)
                    {
                        i.id = id;
                        u_all++;
                        bool ok =  _globals._repositories.sr.Update(i);
                        if(ok) u_ok++;
                    } else{
                        zInfo("no id for excelId: "+QString::number(i.excelId));
                    }
                } else{
                    i_all++;
                    bool ok =  _globals._repositories.sr.Add(i);
                    if(ok) i_ok++;
                }
            }
            zInfo(QStringLiteral("Updated: %1/%2").arg(u_ok).arg(u_all))
            zInfo(QStringLiteral("Inserted: %1/%2").arg(i_ok).arg(i_all))
        } else{
            zInfo("no items to import");
        }
    } else{
        zInfo("file failed");
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

void MainPresenter::processSoldItemAction(IMainView *sender){
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
    QList<County> counties = _globals._repositories.cr.GetAll();
    // rekordok -> model lista
    DataRowDefaultModel cd = County::To_DataRowDefaultModel(counties);
    cd.name = QT_STRINGIFY(county); // ennek a mezőnek lesznek ezek a defaultjai
    //QList<DataRowDefaultModel> d {{cd}};
    //model->dataForm->SetDataRowDefaults(d);


    QList<Article> articles = _globals._repositories.ar.GetAll();
    // rekordok -> model lista
    DataRowDefaultModel ad = Article::To_DataRowDefaultModel(articles);
    ad.name = QT_STRINGIFY(productName); // ennek a mezőnek lesznek ezek a defaultjai

    QList<DataRowDefaultModel> da {cd,ad};

    model->dataForm->SetDataRowDefaults(da);

    model->dataForm->show();
    QObject::connect(model->dataForm, SIGNAL(AcceptActionTriggered(QUuid)),
                     this, SLOT(processAcceptAction(QUuid)));


   // zInfo("platty");
}

void MainPresenter::processAcceptAction(QUuid opId)
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
            _globals._repositories.sr.Add(data);
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

    bool isDbValid = _globals._helpers._sqlHelper.dbIsValid();
    if(isDbValid){
        MainViewModel::StringModel fn = sender->get_CimCSVFileName();

        FileHelper::CSVModel csvModel = FileHelper::LoadCSV(fn.str);
        if(csvModel.error == FileHelper::Ok){
            zInfo("file ok");
            QList<Address> items = Address::CSV_Import(csvModel.records);

            // megvan a modell lista, egyenként meg kell nézni excel_id szerint, hogy
            // ha létezik, update
            // ha nem, insert
            // todo 001 storno flag
            // todo 002 partner törzs - partner id bevezetése
            // - 1. partner import
            // - 2. tétel import
            //SoldItemRepository::InsertOrUpdate(items);

            SqlRepository<Address>& repo =  _globals._repositories.address;

            if(!items.isEmpty())
            {
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
                zInfo(QStringLiteral("Updated: %1/%2").arg(u_ok).arg(u_all))
                    zInfo(QStringLiteral("Inserted: %1/%2").arg(i_ok).arg(i_all))
            } else{
                zInfo("no items to import");
            }
        }
        else
        {
            zWarning("file failed");
        }
    }
    else
    {
        zWarning("db is invalid");
    }
    Operations::instance().stop(opId);
}
