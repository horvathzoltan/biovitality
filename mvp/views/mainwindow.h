#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mvp/viewinterfaces/imainview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IMainView
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    void set_DoWorkRModel(const MainViewModel::StringModel& m) override;
    MainViewModel::DoWorkModel get_DoWorkModel() override;
    MainViewModel::StringModel get_TetelCSVFileName() override;
    MainViewModel::StringModel get_CimCSVFileName() override;
    void set_StatusLine(const MainViewModel::StringModel &m) override;
    MainViewModel::StringModel get_StatusLine() override;
    //MainViewModel::StringModel get_CimCSVFileName() override;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void PushButtonActionTriggered(IMainView *sender) override;
    void TetelImport_ActionTriggered(IMainView *sender) override;
    void AddSoldItemActionTriggered(IMainView *sender) override;
    void CimImport_ActionTriggered(IMainView *sender) override;
    //log
    void ToClipBoard_ActionTriggered(IMainView *sender) override;
    void ToLogFile_ActionTriggered(IMainView *sender) override;

    void DBTestActionTriggered(IMainView *sender);

private slots:        
    void on_pushButton_tetelImport_clicked();
    void on_pushButton_dbtest_clicked();
    void on_pushButton_AddSoldItem_clicked();
    void on_pushButton_addressImport_clicked();
    void on_pushButton_ToClipBoard_clicked();
    void on_pushButton_ToLogFile_clicked();
    void on_pushButton_clicked();
};
#endif // MAINWINDOW_H
