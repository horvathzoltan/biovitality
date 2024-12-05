#ifndef MAINPRESENTER_H
#define MAINPRESENTER_H

//#include "actions.h"
//#include "updates.h"

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QUuid>
#include "helpers/sqlhelper.h"
#include "mvp/viewinterfaces/imainview.h"
#include "presenter.h"
#include "repositories/sqlrepository.h"


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

    template<typename T>
    bool Import_CheckRepo(SqlRepository<T>& repo);

    // // imports from file to SQL repo
    template<typename T>
    void Import_private(const MainViewModel::FileNameModel& fn,
                        SqlRepository<T>& repo,
                        const QString& keyColumnName,
                        const QChar& separator);

private slots:
    void processPushButtonAction(IMainView *sender);
    void processDBTestAction(IMainView *sender);
    // Add tetel
    void process_Add_SoldItemAction(IMainView *sender);
    void process_Add_SoldItem_AcceptAction(QUuid opId);
    // CSV Import Tétel
    void process_TetelImport_Action(IMainView *sender);
    // CSV Import Cim
    void process_CimImport_Action(IMainView *sender);
    // CSV Import Partner
    void process_PartnerImport_Action(IMainView *sender);
    // CSV Import Ország
    void process_CountryImport_Action(IMainView *sender);
    void process_CountyImport_Action(IMainView *sender);
    // CSV Imort cikk
    void process_ArticleImport_Action(IMainView *sender);

};

#endif // MAINPRESENTER_H
