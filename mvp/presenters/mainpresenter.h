#ifndef MAINPRESENTER_H
#define MAINPRESENTER_H

//#include "actions.h"
//#include "updates.h"

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QUuid>
#include "mvp/viewinterfaces/imainview.h"
#include "presenter.h"


class IMainView;

class MainPresenter : public Presenter
{
    Q_OBJECT

public:
    explicit MainPresenter(QObject *parent = nullptr);
    void appendView(IMainView *w);
    void initView(IMainView *w) const;

private:
    QList<IMainView*> _views;

    //static IMainView *_logView;

    void refreshView(IMainView *w) const;
    void Error(const QSqlError& err);

    struct DbErr{
        bool isDbValid=false;
        bool isTableExists=false;

        bool isValid(){return isDbValid && isTableExists;}
    };

    void Error2(DbErr err);

private slots:
    void processPushButtonAction(IMainView *sender);

    void processDBTestAction(IMainView *sender);
    void processSoldItemAction(IMainView *sender);
    void processAcceptAction(QUuid opId);

    // CSV Import Tétel
    void process_TetelImport_Action(IMainView *sender);
    // CSV Import Cim
    void process_CimImport_Action(IMainView *sender);
};

#endif // MAINPRESENTER_H
