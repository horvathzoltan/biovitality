#include "dataform.h"
#include "ui_dataform.h"
#include "helpers/logger.h"

DataForm::DataForm(QUuid opId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataForm)
{
    _opId = opId;
    ui->setupUi(this);
}

DataForm::~DataForm()
{
    delete ui;
}

QList<MetaValue> DataForm::GetMetaValues()
{
    QList<MetaValue> m;

    for(int L=ui->verticalLayout->count(),i=0;i<L;i++){
        QWidget *w = ui->verticalLayout->itemAt(i)->widget();
        if(w != nullptr){
            w->
            MetaValue v()

        }
    }
    return m;
}

// void DataForm::on_buttonBox_accepted()
// {
//     // zInfo("DataForm: Accepted");
//     // this->done(QDialog::Accepted);
// }


// void DataForm::on_buttonBox_rejected()
// {
//     zInfo("DataForm: Rejected");

//     this->done(QDialog::Rejected);
// }

void DataForm::accept()
{
     //zInfo("dialog accept");
    emit AcceptActionTriggered(_opId);
}

void DataForm::AddWidget(QWidget *w)
{
    if(w==nullptr) return;

    ui->verticalLayout->addWidget(w);
    //w->setLayout(ui->verticalLayout);    
}

