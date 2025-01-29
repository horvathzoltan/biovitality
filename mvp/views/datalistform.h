#ifndef DATALISTFORM_H
#define DATALISTFORM_H

#include "meta/meta.h"
#include "meta/metavalue.h"
#include <QDialog>
#include <QTableWidgetItem>
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
private slots:
    void on_pushButton_Update_clicked();
    void on_pushButton_Insert_clicked();

private:
    Ui::DataListForm *ui;
    QUuid _opId;

    QMap<QString,int> _metaFieldColumnMap;
    QList<int> _refColumnIxs;

    QString GetColumnNameByItem(QTableWidgetItem *item);

signals:
    void UpdateActionTriggered(int id);
    void InsertActionTriggered();

};
#endif // DATALISTFORM_H
