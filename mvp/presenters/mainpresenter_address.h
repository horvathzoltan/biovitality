#ifndef MAINPRESENTER_ADDRESS_H
#define MAINPRESENTER_ADDRESS_H

#include "mvp/presenters/presenter.h"
#include "mvp/viewinterfaces/imainview.h"

#include <QObject>
#include <QUuid>


class MainPresenter_Address : public Presenter
{
    Q_OBJECT

private:
    //Presenter* _presenter = nullptr;
public:
    MainPresenter_Address(QObject *parent = nullptr);

    void Connect(QObject *view_obj);//, Presenter *p);

private slots:
    // Create
    void process_CreateAddress_Action(IMainView *sender);
    // Update
    void process_UpdateAddress_Action(IMainView *sender);
    // ReadAll
    void process_ListAddress_Action(IMainView *sender);
    // Accept Create/Update
    void process_AcceptAddress_Action(QUuid opId);
    // Done
    void process_DoneAddress_Action(QUuid opId, int r);
    // CSV Import
    void process_ImportAddress_Action(IMainView *sender);
};

#endif // MAINPRESENTER_ADDRESS_H
