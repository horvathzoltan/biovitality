#include "mainpresenter.h"
#include "helpers/logger.h"
#include "helpers/sqlhelper.h"
#include "mainviewmodel.h"
#include "dowork.h"
#include "operations.h"
#include "settings.h"

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

#include <bi/repositories/solditemrepository.h>


extern Settings _settings;
SQLHelper _sqlHelper;

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
    _sqlHelper.Init(_settings._sql_settings);
    bool ok = _sqlHelper.Connect();

    if(_sqlHelper.dbIsValid()){
        zInfo("DB "+_settings._sql_settings.dbname+" is valid");
    } else{
        zInfo("DB "+_settings._sql_settings.dbname+" is invalid");
    }
    //_db.close();

    SoldItem::_meta.Init();
};

void MainPresenter::processPushButtonAction(IMainView *sender){
    qDebug() << "processPushButtonAction";
    auto m = sender->get_DoWorkModel();
    auto rm = DoWork::Work1(m);
    sender->set_DoWorkRModel(rm);
}

void MainPresenter::processTetelImportAction(IMainView *sender)
{
    //qDebug() << "processTetelImportAction";

    QUuid opId = Operations::instance().start(this, sender, __FUNCTION__);

    MainViewModel::StringModel fn = sender->get_TetelCSVFileName();

    FileHelper::CSVModel csvModel = FileHelper::LoadCSV(fn.str);
    if(csvModel.error == FileHelper::Ok){
        zInfo("file ok");
        QList<SoldItem> items = SoldItem::ImportCSV(csvModel.records);

        // megvan a modell lista, egyenként meg kell nézni id szerint, hogy
        // ha létezik, update
        // ha nem, insert
        // todo 001 storno flag
        // todo 002 partner törzs - partner id bevezetése
        // - 1. partner import
        // - 2. tétel import
        //SoldItemRepository::InsertOrUpdate(items);
    } else{
        zInfo("file failed");
    }
    Operations::instance().stop(opId);
}

void MainPresenter::processDBTestAction(IMainView *sender)
{
    // SQLHelper sqlh;
    // sqlh.SetSettings(_settings._sql_settings);

    // static const QString conn = QStringLiteral("conn2");
    // auto db = sqlh.Connect_mariadb(conn, 5000);

    // if(db.isValid()){
    //     zInfo("DB "+_settings._sql_settings.dbname+" is valid");
    // } else{
    //     zInfo("DB "+_settings._sql_settings.dbname+" is invalid");
    // }


    // QSqlQuery query(db);
    // bool isok = db.open();
    // if(isok) {

    //     isok = query.exec(QStringLiteral("SELECT id,partnerName FROM SoldItem;"));

    //     if(isok && query.size()){
    //         while (query.next()) {
    //             QVariant id = query.value("id");
    //             QVariant partnerName = query.value("partnerName");
    //             QString msg = QStringLiteral("id:%1 partnerName:%2")
    //                               .arg(id.toString())
    //                               .arg(partnerName.toString());
    //             zInfo(msg);
    //         }
    //     }
    // }
    // else{

    //     Error(query.lastError());
    //     Error(db.lastError());
    // }
    // db.close();

    //SQLHelper sqlh;
    //sqlh.SetSettings(_settings._sql_settings);

    SoldItemRepository sr;
    // bool a1 = sr.Contains(1);
    // zInfo(QStringLiteral("a1:")+(a1?"true":"false"))
    // bool a2 = sr.Contains(2);
    // zInfo(QStringLiteral("a2:")+(a2?"true":"false"))
    // bool a3 = sr.Contains(3);
    // zInfo(QStringLiteral("a3:")+(a3?"true":"false"))

    auto a = sr.Get(1);
    return;
}

void MainPresenter::Error(const QSqlError& err)
{
    if(err.isValid()) zInfo(QStringLiteral("QSqlError: %1 - %2").arg(err.type()).arg(err.text()));
}


