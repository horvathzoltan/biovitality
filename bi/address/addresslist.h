#ifndef ADDRESSLIST_H
#define ADDRESSLIST_H

//#include "mvp/presenters/mainpresenter.h"
#include "meta/metavalue.h"
#include "mvp/presenters/presenter.h"
#include <QUuid>
#include <QObject>

class AddressList: public QObject
{
    Q_OBJECT


public:
    explicit AddressList(QObject *parent = nullptr);
    void List_Address(QUuid opId, Presenter* presenter);

private slots:
    void process_UpdateAction(QUuid opId, int);
    void process_InsertAction(QUuid opId);
    void process_TableFresh_AddRow(QUuid opId, const QList<MetaValue> &values);
    void process_TableFresh_UpdateRow(QUuid opid, const QList<MetaValue> &values);
    void process_DoneAction(QUuid opId, int r);

};

#endif // ADDRESSLIST_H
