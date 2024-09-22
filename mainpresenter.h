#ifndef MAINPRESENTER_H
#define MAINPRESENTER_H

//#include "actions.h"
//#include "updates.h"

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QUuid>
#include "imainview.h"
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
private slots:
    void processPushButtonAction(IMainView *sender);

    void processDBTestAction(IMainView *sender);
    void processSoldItemAction(IMainView *sender);
    void processAcceptAction(QUuid opId);

    // CSV Import Tétel
    void processTetelImportAction(IMainView *sender);
    // CSV Import Cim
    void processCimImportAction(IMainView *sender);
};

#endif // MAINPRESENTER_H
