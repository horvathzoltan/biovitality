#include <QApplication>
#include <QtCharts>
#include "buildnumber.h"

#include "helpers/logger.h"
#include "helpers/stringify.h"
#include "mainwindow.h"
#include "mainpresenter.h"

auto main(int argc, char *argv[]) -> int
{
#if defined (STRINGIFY_H) && defined (STRING) && defined (TARGI)
    QString target = STRING(TARGI);
#else
    auto target=QStringLiteral("ApplicationNameString");
#endif

    QCoreApplication::setApplicationVersion(Buildnumber::_value);
    QCoreApplication::setOrganizationName("LogControl Kft.");
    QCoreApplication::setOrganizationDomain("https://www.logcontrol.hu/");

    Logger::Init(Logger::ErrLevel::INFO, Logger::DbgLevel::TRACE, true, true);
    QString user = qgetenv("USER");
    zInfo(QStringLiteral("started ")+target+" as "+user + " build:"+ Buildnumber::_value);
    //FileNameHelper::Init(QCoreApplication::applicationDirPath());
    //bool settings_ok = settings.Load(FileNameHelper::SettingsFileName());
    //if(settings_ok){
    //    zInfo("settings loaded")
    //}

    QApplication a(argc, argv);


    MainWindow w;
    MainPresenter p;
    p.appendView(&w);
    w.show();    
    p.initView(&w);

    return a.exec();
}
