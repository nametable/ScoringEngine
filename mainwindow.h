#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "pathexistscorechecker.h"
#include "valuescorechecker.h"
#include "scriptscorechecker.h"
#include "myscoringmodel.h"
#include "mydelegate.h"
#include "scorecheckingconfig.h"
#include <QStandardItemModel>
#include <vector>
#include <QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionExit_triggered();

    void on_actionInsert_Blank_triggered();

    void on_actionConfiguration_Prefs_triggered();

    void on_actionSave_Config_triggered();

    void on_actionOpen_Config_triggered();
    void scoreupdate();

    void on_actionTimer_Start_toggled(bool arg1);

    void on_actionNew_Config_triggered();

private:
    Ui::MainWindow *ui;
    MyScoringModel *scoringmodel;
    MyDelegate *scoringdelegate;
    QStandardItemModel *standardmodel;
    std::vector<BaseScoreChecker*> *vecScoreCheckers;
    ScoreCheckingConfig *config;
    QTimer *timer;
    void SetupTable();
    void TestScoreCheckers();

};

#endif // MAINWINDOW_H
