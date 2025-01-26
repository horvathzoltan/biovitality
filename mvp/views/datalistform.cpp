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

    int i=0;
    for (MetaValue &metaValue : a)
    {
        QString translatedName = _globals._translator.Translate(metaValue.wcode);
        //int i = ui->tableWidget->columnCount();
        ui->tableWidget->setHorizontalHeaderItem(i, new QTableWidgetItem(translatedName));
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
