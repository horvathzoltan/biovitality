#ifndef DATALISTFORM_H
#define DATALISTFORM_H

#include "meta/metavalue.h"
#include <QDialog>
#include <QUuid>

namespace Ui {
class DataListForm;
}

class DataListForm : public QDialog
{
    Q_OBJECT

public:
    explicit DataListForm(QUuid opId, QWidget *parent = nullptr);
    ~DataListForm();

    void setMetaValueList(QList<QList<MetaValue>> m);

private:
    Ui::DataListForm *ui;
    QUuid _opId;


};

#endif // DATALISTFORM_H
