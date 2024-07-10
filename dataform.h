#ifndef DATAFORM_H
#define DATAFORM_H

#include "ui_dataform.h"
#include <QDialog>
#include <QVBoxLayout>

namespace Ui {
class DataForm;
}

class DataForm : public QDialog
{
    Q_OBJECT

public:
    explicit DataForm(QWidget *parent = nullptr);
    ~DataForm();



private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();


private:
    Ui::DataForm *ui;

public:
    QVBoxLayout* GetLayout(){ return ui->verticalLayout;}
};

#endif // DATAFORM_H
