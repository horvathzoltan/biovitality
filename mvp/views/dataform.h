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

class DataForm : public QDialog{
    Q_OBJECT

public:
    struct DataModel
    {
    public:
        QList<MetaValue> values;
        QList<MetaValidationMessage> validations;

        bool isValid(){return validations.isEmpty();}

        QStringList Get_LogMessages()
        {
            QStringList e;
            for(MetaValidationMessage&a:validations)
            {
                QString msg = a.logMessage();
                if(!msg.isEmpty())
                {
                    e.append(msg);
                }
            }
            return e;
        }
    };


    explicit DataForm(QUuid opId, QWidget *parent = nullptr);
    ~DataForm();

    void setMetaValues(QList<MetaValue> m);
    DataModel Get_MetaValues();
    void SetValidations(QList<MetaValidationMessage> validations);
    void SetDataRowDefaults(QList<DataRowDefaultModel> v);
    //void SetDataRowReferences(QList<DataRowDefaultModel> v);

//private slots:
    //void on_buttonBox_accepted();

    //void on_buttonBox_rejected();


private:
    Ui::DataForm *ui;
    QUuid _opId;

    void accept();
    void reject();


    DataRowWidget* FindWidget(const QString& name);
public:
    //QVBoxLayout* GetLayout(){ return ui->verticalLayout;}
    void AddWidget(QWidget* w);

    void done(int r);

signals:
    void AcceptActionTriggered(QUuid);
    void RejectActionTriggered(QUuid);
    void DoneActionTriggered(QUuid, int r);
};

#endif // DATAFORM_H
