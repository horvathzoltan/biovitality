#include "dataform.h"
#include "infrastructure/globals.h"
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
    zWarning("Cannot find widget for dataRow: "+name);
    return nullptr;
}

DataForm::DataModel DataForm::Get_MetaValues()
{
    DataModel m;

    for(int L=ui->verticalLayout->count(),i=0;i<L;i++){
        QWidget *w = ui->verticalLayout->itemAt(i)->widget();
        if(w != nullptr){
            DataRowWidget *dataRowWidget = reinterpret_cast<DataRowWidget*>(w);
            if(dataRowWidget){
                MetaValue v = dataRowWidget->metaValue();
                QVariant v2 = dataRowWidget->value();
                QVariant v22(v2);
                // if(v.metaField_name=="countyId"){
                //     zInfo("countyId");
                // }

                QMetaType destType = v.type;
                // 001c1 QString -> optional<int> megírni a convert-ot

                bool canConvert = v2.canConvert(destType);
                if(canConvert)
                {
                    bool ok = v2.convert(destType);
                    if(ok){
                        v.value.setValue(v2);
                        dataRowWidget->SetValidateLabel("");
                    }
                }
                else
                {
                    MetaValidationMessage e(
                        v.metaField_name,
                        GetWCode(WCodes::Validation::CannotConvert),
                        QStringLiteral("Cannot convert ")
                                      +v.metaField_name +" = " + v22.toString() +", "+
                        QStringLiteral("no converter registered from ")
                                      +v22.typeName()+" to "+ destType.name()
                        );
                    m.validations.append(e);                    
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
        DataRowWidget* w = FindWidget(validation.name());
        if(w){
            QString msg = _globals._translator.Translate(validation.wcode());
            w->SetValidateLabel(msg);
        }else{
            zWarning("Cannot set validation for dataRow: "+validation.name());
        }
    }
}

void DataForm::SetDataRowDefaults(QList<DataRowDefaultModel> values)
{
    for (DataRowDefaultModel &v : values) {
        QString dataRowName = v.name();
        DataRowWidget *w = FindWidget(dataRowName);
        if (w) {
            w->SetDataRowDefault(v.values());
        } else {
            zWarning("Cannot set defaults for dataRow: " + dataRowName);
        }
    }
}

// void DataForm::SetDataRowReferences(QList<DataRowDefaultModel> values)
// {
//     for (DataRowDefaultModel &v : values) {
//         QString dataRowName = v.name();
//         DataRowWidget *w = FindWidget(dataRowName);
//         if (w) {
//             w->SetDataRowReference(v.values());
//         } else {
//             zWarning("Cannot set references for dataRow: " + dataRowName);
//         }
//     }
// }



void DataForm::setMetaValues(QList<MetaValue> m)
{
    int w0=0;
    QLabel l0;
    QFont f0 = l0.font();
    f0.setPointSize(10);

    // todo 001 az m-et át lehet adni a formnak, hogy építse föl magát
    // todo 002 a modelben át lehetne adni az értékkészletet amiből választani lehet

    for (MetaValue &a : m) {
        a.translatedName = _globals._translator.Translate(a.wcode);
        int i = l0.fontMetrics().boundingRect(a.translatedName).width();
        if (i > w0) w0 = i;
    }


    int i = 0;
    for (MetaValue &metaValue : m) {
        bool isDarkRow = i++%2==0;
        DataRowWidget *w = new DataRowWidget(metaValue, w0, isDarkRow, _globals._settings._autoComplete_millisec);
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
    emit AcceptActionTriggered(_opId);
}

void DataForm::reject()
{
    QDialog::reject();
    emit RejectActionTriggered(_opId);
}

void DataForm::done(int r)
{
    QDialog::done(r);
    emit DoneActionTriggered(_opId, r);
}


void DataForm::AddWidget(QWidget *w)
{
    if(w==nullptr) return;

    ui->verticalLayout->addWidget(w);
    //w->setLayout(ui->verticalLayout);    
}


