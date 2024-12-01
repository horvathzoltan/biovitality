#ifndef LOGPRESENTER_H
#define LOGPRESENTER_H

#include "mvp/viewinterfaces/ilogview.h"
#include "presenter.h"

class IMainView;

class LogPresenter : public Presenter
{
    Q_OBJECT

public:
    explicit LogPresenter(QObject *parent = nullptr);
    void appendView(IMainView *w);

    static void Log(const QString& str);
private:
    static IMainView *_logView;
    //QList<IMainView*> _views;

    static QString ColorizeLog(const QString &str);
    static QString GetLogColor(const QString &str);
    static QString ColorizeLog2(const QString &str, const QString &c);

private slots:
    void processToClipBoard_Action(IMainView *sender);
    void processToLogFile_Action(IMainView *sender);

};

#endif // LOGPRESENTER_H
