#ifndef ADDRESSOPERATIONS_H
#define ADDRESSOPERATIONS_H

#include "mvp/presenters/presenter.h"
#include "mvp/viewinterfaces/iview.h"

#include <QUuid>
#include <mvp/viewmodels/mainviewmodel.h>

class AddressOperations
{
public:
    //static void Operation_UpdateAddress(QUuid opId, int id);
    //static void Operation_InsertAddress();
    static void Operation_UpdateAddress(Presenter *presenter, IView *sender, QUuid opId, int id);
    static void Operation_InsertAddress(Presenter *presenter, IView *sender);

private:
    static void CreateUpdate_Address(QUuid opId);

public:
    // CSV Import Cim
    struct Import1Result{
    private:
        bool _isRepoOk = false;
        QUuid _opId = QUuid();

    public:
        void setOpId(QUuid opId){_opId = opId;};
        void setRepoOk(bool v){_isRepoOk = v;};
        bool isValid(){return _isRepoOk;}
        QUuid opId(){return _opId;}
    };

    static Import1Result Operation_ImportAddress1(Presenter *presenter, IView *sender);
    static void Operation_ImportAddress2(const MainViewModel::FileNameModel& fn);
};

#endif // ADDRESSOPERATIONS_H
