#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imainview.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow, public IMainView
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    void set_DoWorkRModel(const MainViewModel::StringModel& m);
    MainViewModel::DoWorkModel get_DoWorkModel();
    MainViewModel::StringModel get_TetelCSVFileName();
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
signals:
    void PushButtonActionTriggered(IMainView *sender);
    void TetelImportActionTriggered(IMainView *sender);
    void DBTestActionTriggered(IMainView *sender);
private slots:    
    void on_pushButton_clicked();
    void on_pushButton_tetelImport_clicked();
    void on_pushButton_dbtest_clicked();
};
#endif // MAINWINDOW_H
