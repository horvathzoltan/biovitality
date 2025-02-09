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

    void done(int r);

    void AddRow(const QList<MetaValue>& values);
    void UpdateRow(const QList<MetaValue>& values);
    void setHeaderLine(const QList<MetaValue> &h0);
private:
    Ui::DataListForm *ui;
    QUuid _opId;

    int _idColumnIx=0;
    int _currentId;
    QList<DataRowDefaultModel> _dataRowDefaultModels;
    //void accept();
    //void reject();

    DataRowDefaultModel* FindDefaults(const QString& fieldName);

    QMap<QString,int> _metaFieldColumnMap;
    QList<int> _refColumnIxs;

    QString GetColumnNameByItem(QTableWidgetItem *item);
    void UpdateRow_private(int rowIx, const QList<MetaValue>& values);
    int FindRow(int id);
    bool RowIxIsValid(int rowIx);
private slots:
    void on_pushButton_Update_clicked();
    void on_pushButton_Insert_clicked();

    void on_tableWidget_itemSelectionChanged();

signals:
    void UpdateActionTriggered(QUuid, int);
    void InsertActionTriggered(QUuid);
    void DoneActionTriggered(QUuid, int r);

};
#endif // DATALISTFORM_H
