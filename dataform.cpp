#include "dataform.h"
#include "ui_dataform.h"
#include "helpers/logger.h"

DataForm::DataForm(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataForm)
{
    ui->setupUi(this);
}

DataForm::~DataForm()
{
    delete ui;
}

void DataForm::on_buttonBox_accepted()
{
    zInfo("DataForm: Accepted");
    this->done(QDialog::Accepted);
}


void DataForm::on_buttonBox_rejected()
{
    zInfo("DataForm: Rejected");

    this->done(QDialog::Rejected);
}

void DataForm::AddWidget(QWidget *w)
{
    if(w==nullptr) return;

    ui->verticalLayout->addWidget(w);
    //w->setLayout(ui->verticalLayout);
}

