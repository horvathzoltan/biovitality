#include <QApplication>
#include <QtCharts>
#include <infrastructure/globals.h>
#include <helpers/signalhelper.h>
#include <helpers/filenamehelper.h>
#include "infrastructure/buildnumber.h"
#include "helpers/logger.h"
#include "helpers/stringify.h"
#include "mvp/views/mainwindow.h"
#include "mvp/presenters/mainpresenter.h"
#include "mvp/presenters/logpresenter.h"

Globals _globals;

auto main(int argc, char *argv[]) -> int
{
    SignalHelper::setShutDownSignal(SignalHelper::SIGINT_); // shut down on ctrl-c
    SignalHelper::setShutDownSignal(SignalHelper::SIGTERM_); // shut down on killall

#if defined (STRINGIFY_H) && defined (STRING) && defined (TARGI)
    QString target = STRING(TARGI);
#else
    auto target=QStringLiteral("ApplicationNameString");
#endif    

    QCoreApplication::setApplicationVersion(Buildnumber::_value);
    QCoreApplication::setOrganizationName("horvathzoltan");
    QCoreApplication::setOrganizationDomain("https://github.com/horvathzoltan");

    Logger::Init(Logger::ErrLevel::INFO, Logger::DbgLevel::TRACE, false, false);

    //FileNameHelper::Init(QCoreApplication::applicationDirPath());
    //bool settings_ok = settings.Load(FileNameHelper::SettingsFileName());
    //if(settings_ok){
    //    zInfo("settings loaded")
    //}

    QApplication a(argc, argv);
    FileNameHelper::Init();

    //SoldItem data;
    //County c;

    _globals._translator.Init();

    MainWindow w;
    MainPresenter p;        
    p.appendView(&w);

    LogPresenter logPresenter;
    logPresenter.appendView(&w);
    Logger::SetFunction(&LogPresenter::Log);


    // innen tudunk loggolni
    QString user = qgetenv("USER");
    zInfo(QStringLiteral("started ")+target+" as "+user + " build:"+ Buildnumber::_value);

    zInfo("testdata_path:"+FileNameHelper::GetTestFolderPath());
    zInfo("working_folder:"+FileNameHelper::GetWorkingFolder());


    w.show();    
    p.initView(&w);


    return a.exec();
}
