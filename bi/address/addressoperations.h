#ifndef ADDRESSOPERATIONS_H
#define ADDRESSOPERATIONS_H

#include "mvp/presenters/presenter.h"
#include "mvp/viewinterfaces/iview.h"

#include <QUuid>
class AddressOperations
{
public:
    //static void Operation_UpdateAddress(QUuid opId, int id);
    //static void Operation_InsertAddress();
    static void Operation_UpdateAddress(Presenter *presenter, IView *sender, QUuid opId, int id);
    static void Operation_InsertAddress(Presenter *presenter, IView *sender);

    static void CreateUpdate_Address(QUuid opId);

};

#endif // ADDRESSOPERATIONS_H
