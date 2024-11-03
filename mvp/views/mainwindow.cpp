#include "mainwindow.h"
#include "helpers/logger.h"
#include "ui_mainwindow.h"
#include "QDebug"
//#include "imainview.h"
#include "infrastructure/settings.h"

#include <QFileDialog>
#include <QSettings>

#include <helpers/filenamehelper.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);   
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::set_DoWorkRModel(const MainViewModel::StringModel& m)
{
    ui->label->setText(m.str);
};

auto MainWindow::get_DoWorkModel() -> MainViewModel::DoWorkModel
{
    auto t = ui->label->text();
    bool isok;
    int i = t.toInt(&isok, 10);
    if(!isok) return {-1};
    return {i};
}

MainViewModel::FileNameModel MainWindow::get_TetelCSVFileName()
{
    QString fileName = Settings::Get_TetelCSVFileName();
    MainViewModel::FileNameModel r = get_CSVFileName_private(fileName);    
    if(r.IsValid()) Settings::Set_TetelCSVFileName(r.fileName);
    return r;
};

MainViewModel::FileNameModel MainWindow::get_CimCSVFileName()
{
    QString fileName = Settings::Get_CimCSVFileName();
    MainViewModel::FileNameModel r = get_CSVFileName_private(fileName);
    if(r.IsValid()) Settings::Set_CimCSVFileName(r.fileName);
    return r;
};

MainViewModel::FileNameModel MainWindow::get_PartnerCSVFileName()
{
    QString fileName = Settings::Get_PartnerCSVFileName();
    MainViewModel::FileNameModel r = get_CSVFileName_private(fileName);
    if(r.IsValid()) Settings::Set_PartnerCSVFileName(r.fileName);
    return r;
};

MainViewModel::FileNameModel MainWindow::get_CSVFileName_private(const QString& fileName){
    MainViewModel::FileNameModel r;

    bool hasFileName = !fileName.isEmpty();

    r.fileName = QFileDialog::getOpenFileName(this,
                                         tr("Open File"),
                                         hasFileName
                                             ?fileName
                                             :FileNameHelper::GetTestFolderPath(),
                                         tr("CSV Files (*.csv *.txt)"));

    r.isCanceled = r.fileName.isNull();
    return r;
}

void MainWindow::set_StatusLine(const MainViewModel::StringModel &m)
{
    if(m.str.isEmpty()) return;

    QString u;
    for(auto&a:m.str){
        if(a == '\r'){
            QTextCursor cursor = ui->plainTextEdit_status->textCursor();
            cursor.movePosition(QTextCursor::End);
            cursor.select(QTextCursor::LineUnderCursor);
            cursor.removeSelectedText();
            cursor.deletePreviousChar(); // Added to trim the newline char when removing last line
            ui->plainTextEdit_status->setTextCursor(cursor);
        } else if (a == '\n') {
            if(!u.isEmpty()){
                ui->plainTextEdit_status->appendHtml(u);//a.join('\n'));//setPlainText(a.join('\n'));
                u.clear();
            }
        }
        else{
            u.append(a);
        }
    }
    if(!u.isEmpty()){
        ui->plainTextEdit_status->appendHtml(u);
    }
}

MainViewModel::StringModel MainWindow::get_StatusLine() {
    MainViewModel::StringModel r;

    r.str = ui->plainTextEdit_status->toPlainText();

    return r;
}


//add
void MainWindow::on_pushButton_AddSoldItem_clicked()
{
    zTrace();
    emit Add_SoldItem_ActionTriggered(this);
}

//import

void MainWindow::on_pushButton_TetelImport_clicked()
{
    zTrace();
    emit TetelImport_ActionTriggered(this);
}

void MainWindow::on_pushButton_AddressImport_clicked()
{
    zTrace();
    emit CimImport_ActionTriggered(this);
}

void MainWindow::on_pushButton_PartnerImport_clicked()
{
    zTrace();
    emit PartnerImport_ActionTriggered(this);
}

void MainWindow::on_pushButton_CountryImpot_clicked()
{
    zTrace();
    emit CountryImpot_ActionTriggered(this);
}

//test
void MainWindow::on_pushButton_dbtest_clicked()
{
    zTrace();
    emit DBTestActionTriggered(this);
}


//log
void MainWindow::on_pushButton_ToClipBoard_clicked()
{
    zTrace();
    emit ToClipBoard_ActionTriggered(this);
}


void MainWindow::on_pushButton_ToLogFile_clicked()
{
    zTrace();
    emit ToLogFile_ActionTriggered(this);
}




