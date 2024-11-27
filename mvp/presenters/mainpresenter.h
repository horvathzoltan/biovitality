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

    struct CSVErrModel{
    private:
        QString _fileName;
        int _itemsCount;
        int _recordsCount;

        CSVErrModel(){};
    public:

        CSVErrModel(const QString& fn){
            _fileName = fn;
            _itemsCount= 0;
            _recordsCount = 0;
        }

        void setRecordsCount(int v){ _recordsCount = v;}
        void setItemsCount(int v){ _itemsCount = v;}

        QString ToSting(){
            return QStringLiteral("%1 (%2/%3)")
                      .arg(_fileName)
                      .arg(_itemsCount)
                      .arg(_recordsCount);
        }
    };

private:
    QList<IMainView*> _views;

    //static IMainView *_logView;

    void refreshView(IMainView *w) const;
    void Error(const QSqlError& err);



    //void Error2(SQLHelper::DbErr err);

    // template<typename T>
    // static void InsertOrUpdate(SqlRepository<T>& repo, QList<T>& items);

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
};

#endif // MAINPRESENTER_H
