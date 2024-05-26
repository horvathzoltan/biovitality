#include "mainpresenter.h"
#include "helpers/logger.h"
#include "helpers/sqlhelper.h"
#include "mainviewmodel.h"
#include "dowork.h"
#include "operations.h"

#include <QFileDialog>
#include <QDateTime>

#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>

#include <helpers/filehelper.h>
#include <helpers/sqlhelper.h>

#include <bi/models/solditem.h>

#include <repositories/solditemrepository.h>
#include <repositories/solditemrepository.h>

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

    //refreshView(w);
}

void MainPresenter::refreshView(IMainView *w) const { Q_UNUSED(w) };

void MainPresenter::initView(IMainView *w) const {
    MainViewModel::StringModel rm{"1"};
    w->set_DoWorkRModel(rm);

    static const QString conn = QStringLiteral("conn1");
    SQLHelper::SQLSettings sql_settings{
        "QMARIADB",
        "biovitality",
            {{"192.168.1.105", 3306}},
        "zoli",
        "Aladar123"
    };
    SQLHelper sqlh;
    auto db = sqlh.Connect(sql_settings, conn, 5000);

    if(db.isValid()){
        zInfo("DB "+sql_settings.dbname+" is valid");
    } else{
        zInfo("DB "+sql_settings.dbname+" is invalid");
    }
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

        SoldItemRepository::InsertOrUpdate(items);
    } else{
        zInfo("file failed");
    }
    Operations::instance().stop(opId);
}

