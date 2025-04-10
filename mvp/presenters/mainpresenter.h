#ifndef MAINPRESENTER_H
#define MAINPRESENTER_H

//#include "actions.h"
//#include "updates.h"

#include <QList>
#include <QObject>
#include <QSqlError>
#include <QUuid>
#include "bi/operations.h"
#include "meta/meta.h"
//#include "helpers/sqlhelper.h"
#include "mvp/viewinterfaces/imainview.h"
#include "mainpresenter_address.h"
#include "presenter.h"
//#include "repositories/sqlrepository.h"

//#define Get_DataRowDefaultModel(t, r, b) Get_DataRowDefaultModel_<r>(QStringLiteral(#b), sizeof(t::Meta()._instance.b))
//#define Get_DataRowDefaultModel(t, r) Get_DataRowDefaultModel_<r>()

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
    MainPresenter_Address _mainPresenter_Address;

    //static IMainView *_logView;
    void refreshView(IMainView *w) const;
    //void Error(const QSqlError& err);

//    template<typename T>
//    bool Import_CheckRepo(SqlRepository<T>& repo);

    // // imports from file to SQL repo
    template<typename T>
    void Import_private(const MainViewModel::FileNameModel& fn,
                        //SqlRepository<T>& repo,
                        const QString& keyColumnName,
                        const QChar& separator);


    DataRowDefaultModel Copy_DataRowDefaultModel_(const DataRowDefaultModel& v, const QString& f)
    {
        DataRowDefaultModel r(v);
        r.SetName_(f);
        return r;
    }

    QString GetOpname(FormModel_Type amType);


private slots:
    void processPushButtonAction(IMainView *sender);
    void processDBTestAction(IMainView *sender);
    // Add tetel
    void process_Add_SoldItemAction(IMainView *sender);
    void process_Add_SoldItem_AcceptAction(QUuid opId);

    void process_DoneAction(QUuid opId, int r);



    // CSV Import Tétel
    void process_TetelImport_Action(IMainView *sender);

    // CSV Import Partner
    void process_PartnerImport_Action(IMainView *sender);
    // CSV Import Ország
    void process_CountryImport_Action(IMainView *sender);
    void process_CountyImport_Action(IMainView *sender);
    // CSV Imort cikk
    void process_ArticleImport_Action(IMainView *sender);


    void process_PartnerList_Action(IMainView *sender);


// signals:
//     void TableFresh_AddRow(QUuid opid,const  QList<MetaValue>& values);
//     void TableFresh_UpdateRow(QUuid opid,const QList<MetaValue>& values);


    // template<typename T>
    // void process_CreateUpdate_AcceptAction(QUuid opId);
};

#endif // MAINPRESENTER_H
