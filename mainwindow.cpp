#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
//#include "imainview.h"
#include "settings.h"

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

MainViewModel::StringModel MainWindow::get_TetelCSVFileName()
{
    MainViewModel::StringModel r;

    QString fileName = Settings::Get_TetelCSVFileName();
    if(fileName.isEmpty()) fileName = FileNameHelper::GetTestFolderPath();;

    r.str = QFileDialog::getOpenFileName(this,
                                         tr("Open File"),
                                         fileName,
                                         tr("CSV Files (*.csv *.txt)"));

    if(!r.str.isEmpty()) Settings::Set_TetelCSVFileName(r.str);
    return r;
};

MainViewModel::StringModel MainWindow::get_CimCSVFileName()
{
    MainViewModel::StringModel r;

    QString fileName = Settings::Get_CimCSVFileName();
    if(fileName.isEmpty()) fileName = FileNameHelper::GetTestFolderPath();;

    r.str = QFileDialog::getOpenFileName(this,
                                         tr("Open File"),
                                         fileName,
                                         tr("CSV Files (*.csv *.txt)"));

    if(!r.str.isEmpty()) Settings::Set_CimCSVFileName(r.str);
    return r;
};

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



void MainWindow::on_pushButton_tetelImport_clicked()
{
    qDebug() << "TetelImportActionTriggered";
    emit TetelImportActionTriggered(this);
}


void MainWindow::on_pushButton_dbtest_clicked()
{
    qDebug() << "DBTestActionTriggered";
    emit DBTestActionTriggered(this);
}


void MainWindow::on_pushButton_AddSoldItem_clicked()
{
    qDebug() << "AddSoldItemActionTriggered";
    emit AddSoldItemActionTriggered(this);

}


void MainWindow::on_pushButton_addressImport_clicked()
{
    qDebug() << "CimImportActionTriggered";
    emit CimImport_ActionTriggered(this);
}


void MainWindow::on_pushButton_ToClipBoard_clicked()
{
    qDebug() << "ToClipBoard_ActionTriggered";
    emit ToClipBoard_ActionTriggered(this);
}


void MainWindow::on_pushButton_ToLogFile_clicked()
{
    qDebug() << "ToLogFile_ActionTriggered";
    emit ToLogFile_ActionTriggered(this);
}

