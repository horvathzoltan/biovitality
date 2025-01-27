#ifndef DATALISTFORM_H
#define DATALISTFORM_H

#include "meta/meta.h"
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
    
    void SetDataRowDefaults(QList<DataRowDefaultModel>);
private:
    Ui::DataListForm *ui;
    QUuid _opId;

    QMap<QString,int> _metaFieldColumnMap;
    QList<int> _refColumnIxs;

};
#endif // DATALISTFORM_H
