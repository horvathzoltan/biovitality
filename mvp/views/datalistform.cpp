#include "datalistform.h"
#include "infrastructure/globals.h"
#include "ui_datalistform.h"

extern Globals _globals;

DataListForm::DataListForm(QUuid opId, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DataListForm)
{
    _opId = opId;
    ui->setupUi(this);
}

DataListForm::~DataListForm()
{
    delete ui;
}

void DataListForm::setMetaValueList(QList<QList<MetaValue>> m)
{
    QList<MetaValue> a = m.first();

    int columnCount = a.count();
    ui->tableWidget->setColumnCount(columnCount);

    _metaFieldColumnMap.clear();

    int i=0;
    for (MetaValue &metaValue : a)
    {
        QString translatedName = _globals._translator.Translate(metaValue.wcode);
        //int i = ui->tableWidget->columnCount();
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(translatedName));

        _metaFieldColumnMap.insert(metaValue.metaField_name, i);

        if(metaValue.refType == RefType::R_1N)
        {
            _refColumnIxs.append(i);
        }
        i++;
    }

    for(QList<MetaValue>& row : m)
    {
        int rowIx = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowIx);
        int i=0;
        for (MetaValue &metaValue : row)
        {
            QString translatedValue = metaValue.value.toString();
            QTableWidgetItem *item = new QTableWidgetItem(translatedValue);
            ui->tableWidget->setItem(rowIx, i, item);
            i++;
        }
    }
}

void DataListForm::SetDataRowDefaults(QList<DataRowDefaultModel> values)
{
    for (DataRowDefaultModel &v : values) {
        QString dataRowName = v.name();
        //DataRowWidget *w = FindWidget(dataRowName);

        // todo 00 a columt kell megtalálni meta mező név alapján
        // végig kell menni a rowokon
        // a benne lévő id alapján ki kell cserélni az adatot a cellában

        for(auto&v:values){
            auto n = v.name();

            if(_metaFieldColumnMap.contains(n)){
                int c = _metaFieldColumnMap.value(n);
                if(_refColumnIxs.contains(c))
                {
                    // most tudjuk, hogy az adott column referencia-e
                    // végog kell menni a sorokon,
                    // ki kell szedni az item értékét
                    // v-ben azt az elemet, aminek az id-je megegyezik a cella értékével
                    // a v-ben lévő értéket be kell tenni a cellába

                    for(int r=0;r<ui->tableWidget->rowCount();r++){
                        QTableWidgetItem *item = ui->tableWidget->item(r, c);
                        if(item){
                            bool ok;
                            int id = item->data(Qt::DisplayRole).toInt(&ok);

                            if(ok){
                                for(auto&v:v.values()){
                                    if(v.id==id){
                                        item->setText(v.name);
                                    }
                                }
                            }

                        }
                    }
                }
            }
        }
        //ui->tableWidget.col
        // if (w) {
        //     w->SetDataRowDefault(v.values());
        // } else {
        //     zWarning("Cannot set defaults for dataRow: " + dataRowName);
        // }

    }
}
