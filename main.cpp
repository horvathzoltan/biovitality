#include <QApplication>
#include <QtCharts>
#include <infrastructure/globals.h>
#include <helpers/signalhelper.h>
#include <helpers/filenamehelper.h>
#include <helpers/sysinfohelper.h>
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

    QCoreApplication::setApplicationName(target);
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

    // itt initelünk mindet
    FileNameHelper::Init();
    _globals._helpers._sysinfoHelper.Init(target, Buildnumber::_value);
    _globals._translator.Init();

    if(_globals._helpers._sysinfoHelper.hostName()=="pif")
    {
        _globals._settings.SetSqlSettings(
            {
                "QMARIADB",
                "biovitality",
                "192.168.1.105",
                3306,
                "zoli",
                "Aladar123"
            });
    }
    else if(_globals._helpers._sysinfoHelper.hostName()=="hercules")
    {
        _globals._settings.SetSqlSettings(
            {
                "QMARIADB",
                "biovitality",
                "172.16.1.63",
                3306,
                "zoli",
                "Aladar123"
            });
    }

    _globals._helpers._sqlHelper.Init(_globals._settings._sql_settings);

    MainWindow w;
    MainPresenter p;        
    p.appendView(&w);

    // ui log init
    LogPresenter logPresenter;
    logPresenter.appendView(&w);    
    Logger::SetFunction(&LogPresenter::Log);        
    // innen tudunk loggolni a ui-ra

    QString sysInfo = _globals._helpers._sysinfoHelper.Get_SysInfo();
    zInfo(sysInfo);

    zInfo("testdata_path:"+FileNameHelper::GetTestFolderPath());
    zInfo("working_folder:"+FileNameHelper::GetWorkingFolder());

    w.show();    
    p.initView(&w);

    return a.exec();
}
