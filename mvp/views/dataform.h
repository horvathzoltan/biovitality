#ifndef DATAFORM_H
#define DATAFORM_H

#include "ui_dataform.h"
#include <QDialog>
#include <QUuid>
#include <QVBoxLayout>
#include <mvp/views/datarowwidget.h>

namespace Ui {
class DataForm;
}

struct DataModel{
public:
    QList<MetaValue> values;
    QList<MetaValidationMessage> validations;

    bool isValid(){return validations.isEmpty();}
};





class DataForm : public QDialog
{
    Q_OBJECT

public:
    explicit DataForm(QUuid opId, QWidget *parent = nullptr);
    ~DataForm();

    void setMetaValues(QList<MetaValue> m);
    DataModel metaValues();
    void SetValidations(QList<MetaValidationMessage> validations);
    void SetDataRowDefaults(QList<DataRowDefaultModel> v);

//private slots:
    //void on_buttonBox_accepted();

    //void on_buttonBox_rejected();


private:
    Ui::DataForm *ui;
    QUuid _opId;

    void accept();
    DataRowWidget* FindWidget(const QString& name);
public:
    //QVBoxLayout* GetLayout(){ return ui->verticalLayout;}
    void AddWidget(QWidget* w);

signals:
    void AcceptActionTriggered(QUuid);
};

#endif // DATAFORM_H
