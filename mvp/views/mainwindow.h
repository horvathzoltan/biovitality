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
    MainViewModel::FileNameModel get_CSVFileName_SoldItem() override;
    MainViewModel::FileNameModel get_CSVFileName_Address() override;
    MainViewModel::FileNameModel get_CSVFileName_Partner() override;
    MainViewModel::FileNameModel get_CSVFileName_Country() override;
    MainViewModel::FileNameModel get_CSVFileName_County() override;
    MainViewModel::FileNameModel get_CSVFileName_Article() override;

    MainViewModel::FileNameModel get_CSVFileName_private(const QString& fileName);
    void set_StatusLine(const MainViewModel::StringModel &m) override;
    MainViewModel::StringModel get_StatusLine() override;
    //MainViewModel::StringModel get_CimCSVFileName() override;
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    template<typename T>
    QString get_CSVFileName();

    void Translate();

signals:
    void PushButtonActionTriggered(IMainView *sender) override;
    //add
    void Add_SoldItem_ActionTriggered(IMainView *sender) override;
    void Add_Address_ActionTriggered(IMainView *sender) override;
    void Update_Address_ActionTriggered(IMainView *sender) override;

    // list
    void AddressList_ActionTriggered(IMainView *sender) override;

    //import
    void TetelImport_ActionTriggered(IMainView *sender) override;    
    void CimImport_ActionTriggered(IMainView *sender) override;
    void PartnerImport_ActionTriggered(IMainView *sender) override;
    void CountryImport_ActionTriggered(IMainView *sender) override;
    void ArticleImport_ActionTriggered(IMainView *sender) override;
    void CountyImport_ActionTriggered(IMainView *sender) override;

    //test
    void DBTestActionTriggered(IMainView *sender);
    //log
    void ToClipBoard_ActionTriggered(IMainView *sender) override;
    void ToLogFile_ActionTriggered(IMainView *sender) override;

private slots:
//add
    void on_pushButton_AddSoldItem_clicked();
//import
    void on_pushButton_AddressImport_clicked();
    void on_pushButton_PartnerImport_clicked();
    void on_pushButton_TetelImport_clicked();
//test
    void on_pushButton_dbtest_clicked();
//log
    void on_pushButton_ToClipBoard_clicked();
    void on_pushButton_ToLogFile_clicked();

    void on_pushButton_CountryImpot_clicked();
    void on_pushButton_ArticleImport_clicked();
    void on_pushButton_CoutntyImport_clicked();
    void on_pushButton_AddressCreate_clicked();
    void on_pushButton_AddressUpdate_clicked();
    void on_pushButton_AddressList_clicked();
};
#endif // MAINWINDOW_H
