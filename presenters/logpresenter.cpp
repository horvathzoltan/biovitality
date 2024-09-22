#include "logpresenter.h"

#include "globals.h"
#include "imainview.h"

extern Globals _globals;

IMainView* LogPresenter::_logView = nullptr;

LogPresenter::LogPresenter(QObject *parent):Presenter(parent){}

void LogPresenter::appendView(IMainView *w)
{
    if(_logView) return;
    _logView = w;
    Logger::SetFunction(&LogPresenter::Log);
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
    if(str.startsWith("WARNING:")) return ColorizeLog2(str, "orange>");
    if(str.startsWith("DEBUG:")) return ColorizeLog2(str, "yellow>");
    if(str.startsWith("TRACE:")) return ColorizeLog2(str, "green");
    return str;
}
