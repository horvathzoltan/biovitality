#include "dataform.h"
#include "globals.h"
#include "ui_dataform.h"
#include "helpers/logger.h"
#include "helpers/translator.h"
extern Globals _globals;

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

DataRowWidget *DataForm::FindWidget(const QString &name)
{
    for(int L=ui->verticalLayout->count(),i=0;i<L;i++){
        QWidget *w = ui->verticalLayout->itemAt(i)->widget();
        if(w != nullptr){
            DataRowWidget *dataRowWidget = reinterpret_cast<DataRowWidget*>(w);
            if(dataRowWidget && dataRowWidget->name()==name) return dataRowWidget;
        }
    }
    return nullptr;
}

DataModel DataForm::metaValues()
{
    DataModel m;

    for(int L=ui->verticalLayout->count(),i=0;i<L;i++){
        QWidget *w = ui->verticalLayout->itemAt(i)->widget();
        if(w != nullptr){
            DataRowWidget *dataRowWidget = reinterpret_cast<DataRowWidget*>(w);
            if(dataRowWidget){
                MetaValue v = dataRowWidget->metaValue();
                QVariant v2 = dataRowWidget->value();
                bool ok = v2.convert(v.value.metaType());
                if(ok){
                    v.value.setValue(v2);
                    dataRowWidget->SetValidateLabel("");
                } else{
                    MetaValidationMessage e{
                        .name = v.name,
                        .wcode = GetWCode(WCodes::Validation::CannotConvert),
                        .value = dataRowWidget->text()
                    };
                    m.validations.append(e);
                    //dataRowWidget->SetValidateLabel(e.wcode);
                }
                m.values.append(v);
            }
        }
    }
    return m;
}

void DataForm::SetValidations(QList<MetaValidationMessage> validations)
{
    for(auto&validation:validations){
        DataRowWidget* w = FindWidget(validation.name);
        if(w){
            w->SetValidateLabel(validation.wcode);
        }else{
            zInfo("Cannot set validation:"+validation.name);
        }
    }
}

void DataForm::SetDataRowDefaults(QList<DataRowDefaultModel> values)
{
    for(auto&v:values){
        DataRowWidget* w = FindWidget(v.name);
        if(w){
            w->SetDataRowDefault(v.values);        
        }else{
            zInfo("Cannot set defaults:"+v.name);
        }
    }
}



void DataForm::setMetaValues(QList<MetaValue> m)
{
    int w0=0;
    QLabel l0;
    QFont f0 = l0.font();
    f0.setPointSize(10);

    // todo 001 az m-et át lehet adni a formnak, hogy építse föl magát
    // todo 002 a modelben át lehetne adni az értékkészletet amiből választani lehet
    // todo3
    for (MetaValue &a : m) {
        a.translatedName = _tr(a.wcode);
        int i = l0.fontMetrics().boundingRect(a.translatedName).width();
        if (i > w0) w0 = i;
    }

    int i = 0;
    for (MetaValue &a : m) {
        DataRowWidget *w = new DataRowWidget(a, w0, i++%2==0, _globals._settings._autoComplete_millisec);
        AddWidget(w);
    }
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

