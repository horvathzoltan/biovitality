#include "QDebug"
#include <QFileDialog>
#include <QSettings>

#include "mainwindow.h"
#include "helpers/logger.h"
#include "ui_mainwindow.h"

//#include "imainview.h"
#include "infrastructure/settings.h"
#include "infrastructure/globals.h"

#include "helpers/filenamehelper.h"
#include "helpers/translator.h"

extern Globals _globals;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
      , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Translate();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::Translate()
{
    //import
    ui->groupBox_Import->setTitle(_tr(WCodes::Import));
    ui->pushButton_ArticleImport->setText(_tr(WCodes::Article));
    ui->pushButton_CountryImpot->setText(_tr(WCodes::Country));
    ui->pushButton_CoutntyImport->setText(_tr(WCodes::County));
    ui->pushButton_PartnerImport->setText(_tr(WCodes::Partner));
    //address
    ui->groupBox_Address->setTitle(_tr(WCodes::Address));
    ui->pushButton_AddressCreate->setText(_tr(WCodes::AddNew));
    ui->pushButton_AddressUpdate->setText(_tr(WCodes::Update));
    ui->pushButton_AddressImport->setText(_tr(WCodes::Import));
    //solditem
    ui->pushButton_AddSoldItem->setText(_tr(WCodes::AddNew));
    ui->pushButton_TetelImport->setText(_tr(WCodes::Import));
    //ui->pushButton_UpdateSoldItem->setText(_tr(WCodes::Update));
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

// új cím hozzáadása

void MainWindow::on_pushButton_AddressCreate_clicked()
{
    zTrace();
    emit Add_Address_ActionTriggered(this);
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


void MainWindow::on_pushButton_AddressUpdate_clicked()
{
    zTrace();
    emit Update_Address_ActionTriggered(this);
}

