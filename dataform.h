#ifndef DATAFORM_H
#define DATAFORM_H

#include "ui_dataform.h"
#include <QDialog>
#include <QUuid>
#include <QVBoxLayout>
#include <datarowwidget.h>

namespace Ui {
class DataForm;
}

class DataForm : public QDialog
{
    Q_OBJECT

public:
    explicit DataForm(QUuid opId, QWidget *parent = nullptr);
    ~DataForm();

    QList<MetaValue> GetMetaValues();

//private slots:
    //void on_buttonBox_accepted();

    //void on_buttonBox_rejected();


private:
    Ui::DataForm *ui;
    QUuid _opId;

    void accept();
public:
    //QVBoxLayout* GetLayout(){ return ui->verticalLayout;}
    void AddWidget(QWidget* w);

signals:
    void AcceptActionTriggered(QUuid);
};

#endif // DATAFORM_H
