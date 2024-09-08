#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QDebug"
#include "imainview.h"

#include <QFileDialog>

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

    QString folderPath = FileNameHelper::GetTestFolderPath();
    r.str = QFileDialog::getOpenFileName(this,
                                         tr("Open File"),
                                         folderPath,
                                         tr("CSV Files (*.csv *.txt)"));
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
                ui->plainTextEdit_status->appendPlainText(u);//a.join('\n'));//setPlainText(a.join('\n'));
                u.clear();
            }
        }
        else{
            u.append(a);
        }
    }
    if(!u.isEmpty()){
        ui->plainTextEdit_status->appendPlainText(u);
    }
}

void MainWindow::on_pushButton_clicked()
{
    qDebug() << "PushButtonActionTriggered";
    emit PushButtonActionTriggered(this);
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

