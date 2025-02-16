#ifndef ADDRESSLIST_H
#define ADDRESSLIST_H

#include "mvp/presenters/mainpresenter.h"
#include <QUuid>
#include <QObject>

class AddressList: public QObject
{
    Q_OBJECT


public:
    explicit AddressList(QObject *parent = nullptr);
    void List_Address(QUuid opId, MainPresenter* presenter);

private slots:
    void process_UpdateAction(QUuid opId, int);
    void process_InsertAction(QUuid opId);
    void process_TableFresh_AddRow(QUuid opId, const QList<MetaValue> &values);
    void process_TableFresh_UpdateRow(QUuid opid, const QList<MetaValue> &values);
    void process_DoneAction2(QUuid opId, int r);

};

#endif // ADDRESSLIST_H
