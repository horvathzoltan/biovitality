#include "mainpresenter.h"
#include "helpers/logger.h"
#include "helpers/sqlhelper.h"
#include "mainviewmodel.h"
#include "dowork.h"
#include "operations.h"
//#include "settings.h"
#include "dataform.h"
#include "datarowwidget.h"
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

#include <bi/models/solditem.h>

#include <bi/repositories/sqlrepository.h>

#include <bi/helpers/sqlmetahelper.h>


extern Globals _globals;


MainPresenter::MainPresenter(QObject *parent):Presenter(parent)
{

}

void MainPresenter::appendView(IMainView *w)
{
    if(_views.contains(w)) return;
    _views.append(w);

    auto *view_obj = dynamic_cast<QObject*>(w);

    QObject::connect(view_obj, SIGNAL(PushButtonActionTriggered(IMainView *)),
                     this, SLOT(processPushButtonAction(IMainView *)));

    QObject::connect(view_obj, SIGNAL(TetelImportActionTriggered(IMainView *)),
                     this, SLOT(processTetelImportAction(IMainView *)));

    QObject::connect(view_obj, SIGNAL(DBTestActionTriggered(IMainView *)),
                     this, SLOT(processDBTestAction(IMainView *)));

    QObject::connect(view_obj, SIGNAL(AddSoldItemActionTriggered(IMainView *)),
                     this, SLOT(processSoldItemAction(IMainView *)));


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
        zInfo("DB "+_globals._settings._sql_settings.dbname+" is invalid");
    }
    //_db.close();

    SoldItem::MetaInit();
};

void MainPresenter::processPushButtonAction(IMainView *sender){
    qDebug() << "processPushButtonAction";
    auto m = sender->get_DoWorkModel();
    auto rm = DoWork::Work1(m);
    sender->set_DoWorkRModel(rm);
}

void MainPresenter::processTetelImportAction(IMainView *sender)
{    
    QUuid opId = Operations::instance().start(this, sender, __FUNCTION__);

    MainViewModel::StringModel fn = sender->get_TetelCSVFileName();

    FileHelper::CSVModel csvModel = FileHelper::LoadCSV(fn.str);
    if(csvModel.error == FileHelper::Ok){
        zInfo("file ok");
        QList<SoldItem> items = SoldItem::ImportCSV(csvModel.records);

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
    //auto a = sr.GetAll();
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

    int excelId = 806;

    int id = _globals._repositories.sr.GetIdBy_ExcelId(excelId);
    SoldItem data = _globals._repositories.sr.Get(id);

    QList<MetaValue> m = data.GetMetaValues();


    DataForm *dataForm = new DataForm();

    for(auto&a:m){
        DataRowWidget* w = new DataRowWidget(a.name);
        dataForm->
    }
    //dataForm.SetMetaValues(m);

    dataForm->show();
}

