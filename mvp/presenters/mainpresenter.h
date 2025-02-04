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

    //static IMainView *_logView;
    void refreshView(IMainView *w) const;
    void Error(const QSqlError& err);

//    template<typename T>
//    bool Import_CheckRepo(SqlRepository<T>& repo);

    template<typename T, typename R>
    bool CheckRef_(const QString& f);
    // // imports from file to SQL repo
    template<typename T>
    void Import_private(const MainViewModel::FileNameModel& fn,
                        //SqlRepository<T>& repo,
                        const QString& keyColumnName,
                        const QChar& separator);

    template<typename T, typename R>
    DataRowDefaultModel Get_DataRowDefaultModel_(const QString& f);//const QString& fieldName, unsigned long l);

    DataRowDefaultModel Copy_DataRowDefaultModel_(const DataRowDefaultModel& v, const QString& f)
    {
        DataRowDefaultModel r(v);
        r.SetName_(f);
        return r;
    }

    template<typename T>
    void process_CreateUpdate_AcceptAction(QUuid opId);

    void CreateUpdate_Address(QUuid opId);

    QString GetOpname(AddModel_Type amType);

    void List_Address(QUuid opId);

    void Operation_UpdateAddress(IMainView *sender, int id);
    void Operation_InsertAddress(IMainView *sender);

private slots:
    void processPushButtonAction(IMainView *sender);
    void processDBTestAction(IMainView *sender);
    // Add tetel
    void process_Add_SoldItemAction(IMainView *sender);
    void process_Add_SoldItem_AcceptAction(QUuid opId);

    void process_DoneAction(QUuid opId, int r);
    void process_DoneAction2(QUuid opId, int r);
    // Add Address
    void process_Add_AddressAction(IMainView *sender);
    void process_Update_AddressAction(IMainView *sender);

    void process_CreateUpdate_Address_AcceptAction(QUuid opId);

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

    void process_AddressList_Action(IMainView *sender);


    void process_UpdateAction(QUuid opid, int);
    void process_InsertAction(QUuid opid);

    void process_TableFresh(QUuid opid);

signals:
    void TableFresh(QUuid opid);
};

#endif // MAINPRESENTER_H
