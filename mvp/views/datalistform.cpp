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
    ui->tableWidget->setCurrentItem(nullptr);

}

DataListForm::~DataListForm()
{
    delete ui;
}

// void DataListForm::accept()
// {
//     emit AcceptActionTriggered(_opId);
// }

// void DataListForm::reject()
// {
//     QDialog::reject();
//     emit RejectActionTriggered(_opId);
// }

void DataListForm::done(int r)
{
    QDialog::done(r);
    emit DoneActionTriggered(_opId, r);
}

void DataListForm::AddRow(const QList<MetaValue> &values)
{
    int rowIx = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowIx);
    UpdateRow_private(rowIx, values);
}

void DataListForm::UpdateRow(const QList<MetaValue> &values)
{
    if(values.isEmpty()) return;
    bool ok;
    int id = values[_idColumnIx].value.toInt(&ok);
    if(!ok) return;
    int rowIx = FindRow(id);
    if(rowIx == -1) return;

    UpdateRow_private(rowIx, values);
}

void DataListForm::setHeaderLine(const QList<MetaValue>& h0)
{
    int columnCount = h0.count();
    ui->tableWidget->setColumnCount(columnCount);

    _metaFieldColumnMap.clear();
    for(int i=0;i<columnCount;i++)
    {
        const MetaValue& metaValue = h0[i];
        QString translatedName = _globals._translator.Translate(metaValue.wcode);

        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(translatedName));

        _metaFieldColumnMap.insert(metaValue.metaField_name, i);

        if(metaValue.refType == RefType::R_1N)
        {
            _refColumnIxs.append(i);
        }
    }
}

DataRowDefaultModel* DataListForm::FindDefaults(const QString &fieldName)
{
    if(_dataRowDefaultModels.isEmpty()) return nullptr;
    for (DataRowDefaultModel &a : _dataRowDefaultModels) {
        if(!a.IsValid()) continue;
        if (fieldName == a.name()) {
            return &a;
        }
    }
    return nullptr;
}

void DataListForm::setMetaValueList(QList<QList<MetaValue>> m)
{    
    int rowCount = m.count();
    ui->tableWidget->setRowCount(rowCount);
    for(int i=0;i<rowCount;i++)
    {
        UpdateRow_private(i, m[i]);
    }
}



void DataListForm::UpdateRow_private(int rowIx, const QList<MetaValue> &values)
{
    if(!RowIxIsValid(rowIx)) return;
    if(values.isEmpty()) return;

    int valuesCount = values.count();
    for(int i=0;i<valuesCount;i++)
    {
        const MetaValue &metaValue = values[i];
        QString translatedValue = metaValue.value.toString();
        QTableWidgetItem *item = new QTableWidgetItem(translatedValue);

        if(metaValue.refType == RefType::R_1N){
            bool isRef = _refColumnIxs.contains(i);
            if(isRef){
                DataRowDefaultModel* a = FindDefaults(metaValue.metaField_name);
                if(a){
                    std::optional<int> id;
                    QMetaType qvm = metaValue.value.metaType();
                    auto f_type = QMetaType::fromType<std::optional<int>>();

                    bool cc = QMetaType::canConvert(qvm, f_type);

                    if(cc)
                    {
                        QMetaType::convert(qvm, metaValue.value.constData(), f_type, &id);
                        if(id.has_value()){
                            QString b = a->GetMegnev(id.value());
                            item->setData(Qt::DisplayRole, b);
                        }
                    }
                }
            }
        } else if(metaValue.refType == RefType::R_NM){

        }
        ui->tableWidget->setItem(rowIx, i, item);
    }
}



int DataListForm::FindRow(int id)
{
    for(int r=0;r<ui->tableWidget->rowCount();r++)
    {
        QTableWidgetItem *item = ui->tableWidget->item(r, _idColumnIx);
        if(!item) continue;

        bool ok;
        int rowId = item->data(Qt::DisplayRole).toInt(&ok);
        if(ok && rowId == id)
        {
            return r;
        }
    }
    return -1;
}

bool DataListForm::RowIxIsValid(int rowIx)
{
    if(rowIx<0) return false;
    if(rowIx>=ui->tableWidget->rowCount()) return false;
    return true;
}


void DataListForm::SetDataRowDefaults(QList<DataRowDefaultModel> values)
{
    _dataRowDefaultModels = values;
    for (DataRowDefaultModel &v : values) {
        QString dataRowName = v.name();
        //DataRowWidget *w = FindWidget(dataRowName);

        //  00 a columt kell megtalálni meta mező név alapján
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

QString DataListForm::GetColumnNameByItem(QTableWidgetItem *item) {
    if(!item) return {};

    int column = item->column();
    QTableWidgetItem *headerItem = ui->tableWidget->horizontalHeaderItem(column);
    if (!headerItem) return {};

    return headerItem->text();
}



void DataListForm::on_pushButton_Update_clicked()
{
    zTrace();
    emit UpdateActionTriggered(_opId, _currentId);
}


void DataListForm::on_pushButton_Insert_clicked()
{
    emit InsertActionTriggered(_opId);
}


void DataListForm::on_tableWidget_itemSelectionChanged()
{
    int rowIx = ui->tableWidget->currentRow();
    QTableWidgetItem* item = ui->tableWidget->item(rowIx, _idColumnIx);
    if(!item) return;

    QVariant a = item->data(Qt::DisplayRole);
    bool ok;
    int b = a.toInt(&ok);
    if(!b) return;
    _currentId = b;
}

