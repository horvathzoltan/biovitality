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

MainViewModel::FileNameModel MainWindow::get_CSVFileName_SoldItem()
{
    QString fileName = Settings::Get_CSVFileName_SoldItem();
    MainViewModel::FileNameModel r = get_CSVFileName_private(fileName);    
    if(r.IsValid()) Settings::Set_CSVFileName_SoldItem(r.fileName);
    return r;
};

MainViewModel::FileNameModel MainWindow::get_CSVFileName_Address()
{
    QString fileName = Settings::Get_CSVFileName_Address();
    MainViewModel::FileNameModel r = get_CSVFileName_private(fileName);
    if(r.IsValid()) Settings::Set_CSVFileName_Address(r.fileName);
    return r;
};

MainViewModel::FileNameModel MainWindow::get_CSVFileName_Partner()
{
    QString fileName = Settings::Get_CSVFileName_Partner();
    MainViewModel::FileNameModel r = get_CSVFileName_private(fileName);
    if(r.IsValid()) Settings::Set_CSVFileName_Partner(r.fileName);
    return r;
};

MainViewModel::FileNameModel MainWindow::get_CSVFileName_Country()
{
    QString fileName = Settings::Get_CSVFileName_Country();
    MainViewModel::FileNameModel r = get_CSVFileName_private(fileName);
    if(r.IsValid()) Settings::Set_CSVFileName_Country(r.fileName);
    return r;
};

MainViewModel::FileNameModel MainWindow::get_CSVFileName_County()
{
    QString fileName = Settings::Get_CSVFileName_County();
    MainViewModel::FileNameModel r = get_CSVFileName_private(fileName);
    if(r.IsValid()) Settings::Set_CSVFileName_County(r.fileName);
    return r;
};

MainViewModel::FileNameModel MainWindow::get_CSVFileName_Article()
{
    QString fileName = Settings::Get_CSVFileName_Article();
    MainViewModel::FileNameModel r = get_CSVFileName_private(fileName);
    if(r.IsValid()) Settings::Set_CSVFileName_Article(r.fileName);
    return r;
};
// template<typename T>
// QString MainWindow::get_CSVFileName()
// {
//     QString fileName = Settings::Get_PartnerCSVFileName();
//     return fileName;
// };

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
    emit CountryImport_ActionTriggered(this);
}

void MainWindow::on_pushButton_ArticleImport_clicked()
{
    zTrace();
    emit ArticleImport_ActionTriggered(this);
}

void MainWindow::on_pushButton_CoutntyImport_clicked()
{
    zTrace();
    emit CountyImport_ActionTriggered(this);
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






