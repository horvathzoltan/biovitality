#include "logpresenter.h"

#include "globals.h"
#include "helpers/filenamehelper.h"
#include "imainview.h"

#include <QClipboard>

extern Globals _globals;

IMainView* LogPresenter::_logView = nullptr;

LogPresenter::LogPresenter(QObject *parent):Presenter(parent){}

void LogPresenter::appendView(IMainView *w)
{
    if(_logView) return;
    _logView = w;
    Logger::SetFunction(&LogPresenter::Log);

    auto *view_obj = dynamic_cast<QObject*>(w);

    QObject::connect(view_obj, SIGNAL(ToClipBoard_ActionTriggered(IMainView *)),
                     this, SLOT(processToClipBoard_Action(IMainView *)));

    QObject::connect(view_obj, SIGNAL(ToLogFile_ActionTriggered(IMainView *)),
                     this, SLOT(processToLogFile_Action(IMainView *)));

}

void LogPresenter::Log(const QString& str){

    if(!_logView) return;

    QString msg = ColorizeLog(str);
    _logView->set_StatusLine({msg});
}

QString LogPresenter::ColorizeLog2(const QString& str, const QString& c){
    return QStringLiteral("<p style='color: ")+c+"'>"+str+"</p>";
}

QString LogPresenter::ColorizeLog(const QString& str){
    if(str.startsWith("ERROR:")) return ColorizeLog2(str, "red");
    if(str.startsWith("WARNING:")) return ColorizeLog2(str, "orange");
    if(str.startsWith("DEBUG:")) return ColorizeLog2(str, "yellow");
    if(str.startsWith("TRACE:")) return ColorizeLog2(str, "green");
    return str;
}

void LogPresenter::processToClipBoard_Action(IMainView *sender)
{
    zInfo("processToClipBoard_Action");
    MainViewModel::StringModel r = _logView->get_StatusLine();
    QClipboard *clipboard = QGuiApplication::clipboard();
    clipboard->setText(r.str);
}

void LogPresenter::processToLogFile_Action(IMainView *sender)
{
    zInfo("processToLogFile_Action");
    MainViewModel::StringModel r  = _logView->get_StatusLine();

    if(!r.str.isEmpty())
    {
        QString fileName = FileNameHelper::GetLogFileName();

        FileHelper::FileErrors err;
        bool ok = FileHelper::Save(r.str, fileName, &err, FileHelper::SaveModes::Overwrite);

        zInfo("Log file:"+fileName+" save:"+(ok?"success":"failed"));
    }
}