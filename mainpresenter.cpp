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
    QUuid opId = Operations::instance().startNew(this, sender, __FUNCTION__);

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


    /*
5;Budapest;01
2;Baranya vármegye;02
1;Bács-Kiskun vármegye;03
3;Békés vármegye;04
4;Borsod-Abaúj-Zemplén vármegye;05
6;Csongrád-Csanád vármegye;06
7;Fejér vármegye;07
8;Győr-Moson-Sopron vármegye;08
9;Hajú-Bihar vármegye;09
10;Heves vármegye;10
12;Komárom-Esztergom vármegye;11
13;Nógrád vármegye;12
14;Pest vármegye;13
20;Somogy vármegye;14
15;Szabolcs-Szatmár-Bereg vármegye;15
11;Jász-Nagykun Szolnok vármegye;16
16;Tolna vármegye;17
17;Vas vármegye;18
18;Veszprém vármegye;19
19;Zala vármegye;20
     * */
    QList<DataRowDefaultModel> d
    {
        {
         QT_STRINGIFY(county),
         {
          {5,"Budapest","01"},
          {2,"Baranya vármegye","02"},
          {1,"Bács-Kiskun vármegye","03"},
          {3,"Békés vármegye","04"},
          {4,"Borsod-Abaúj-Zemplén vármegye","05"},
          {6,"Csongrád-Csanád vármegye","06"},
          {7,"Fejér vármegye","07"},
          {8,"Győr-Moson-Sopron vármegye","08"},
          {9,"Hajú-Bihar vármegye","09"},
          {10,";Heves vármegye","10"},
          {12,";Komárom-Esztergom vármegye","11"},
          {13,";Nógrád vármegye","12"},
          {14,";Pest vármegye","13"},
          {20,";Somogy vármegye","14"},
          {15,";Szabolcs-Szatmár-Bereg vármegye","15"},
          {11,";Jász-Nagykun Szolnok vármegye","16"},
          {16,";Tolna vármegye","17"},
          {17,";Vas vármegye","18"},
          {18,";Veszprém vármegye","19"},
          {19,";Zala vármegye","20"}
         }
        }
    };

    model->dataForm->SetDataRowDefaults(d);

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
        }
        else{
            b->dataForm->SetValidations(m.validations);
        }
    }

}

