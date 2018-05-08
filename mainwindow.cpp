#include "mainwindow.h"
#include "ui_mainwindow.h"
//#include "basescorechecker.h"
#include <QFileDialog>
#include "runcommandscorechecker.h"
#include "emptyscorechecker.h"
#include "configpropertieswindow.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    statusBar()->showMessage("Program loaded.");

    config= new ScoreCheckingConfig;
    scoringmodel= new MyScoringModel(this, config->vecScoreCheckers);
    scoringdelegate= new MyDelegate(this);
    SetupTable();

    timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(scoreupdate())); //tell timer to execute scoreupdate()


}
void MainWindow::SetupTable()
{
    ui->mainTable->setModel(this->scoringmodel);
    ui->mainTable->setItemDelegate(this->scoringdelegate);
    ui->mainTable->setDragEnabled(true);
    ui->mainTable->setDropIndicatorShown(true);
    ui->mainTable->setDragDropMode(QAbstractItemView::DragDrop);
    ui->mainTable->setDragDropOverwriteMode(false);
    //leftTableView->setDragDropMode(QAbstractItemView::DragOnly);
    //ui->mainTable->setDragDropMode(QAbstractItemView:: InternalMove);

    QHeaderView *verticalHeader = ui->mainTable->verticalHeader();
    QHeaderView *horizontalHeader = ui->mainTable->horizontalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(30);

    horizontalHeader->setDefaultSectionSize(60);
}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    this->destroy(true, true);
    this->close();
}
void MainWindow::on_actionInsert_Blank_triggered()
{
    //Adds an EmptyScoreChecker() via the model
    scoringmodel->insertChecker(new EmptyScoreChecker());
}
//***************
//  Don't run this code --- please
//  Just a test...
//
void MainWindow::TestScoreCheckers() //This is all a test. Not for production...
{
    ScoreCheckingConfig configtosave;

    PathExistScoreChecker pathcheck;
    saveConfigXML(configtosave,"config_empty.xml");
    configtosave.vecScoreCheckers->push_back(&pathcheck);
    pathcheck.setFilepath("/etc/shadow");
    pathcheck.setDesireExist(true);
    pathcheck.checkState();
    std::cout << "PathCheck returned " << pathcheck.getState() << std::endl;
    RunCommandScoreChecker commandcheck;
    configtosave.vecScoreCheckers->push_back(&commandcheck);
    commandcheck.setCommand("sysctl net.ipv4.ip_forward");
    commandcheck.setSearchString("net.ipv4.ip_forward = 0");
    commandcheck.setSearchExist(false);
    commandcheck.executeCommand();
    commandcheck.checkState();
    std::cout << "CommandCheck returned " << commandcheck.getState() << std::endl;
    ValueScoreChecker valuecheck;
    configtosave.vecScoreCheckers->push_back(&valuecheck);
    valuecheck.setFilepath("/etc/ssh/sshd_config");
    valuecheck.setDesireExist(true);
    valuecheck.setSearchString("\nPermitRootLogin no");
    valuecheck.checkState();
    std::cout << "ValueCheck returned " << valuecheck.getState() << std::endl;
    ScriptScoreChecker scriptcheck;
    configtosave.vecScoreCheckers->push_back(&scriptcheck);
    scriptcheck.setScript("#!/bin/bash\n"
                          "ls\n"
                          "lsattr /etc/passwd\n"
                          "#ps\n");
    scriptcheck.setSearchString("--------------e---- /etc/passwd");
    scriptcheck.setDesiredState(true);
    scriptcheck.checkState();
    std::cout << "ScriptCheck returned " << scriptcheck.getState() << std::endl;

    saveConfigXML(configtosave,"config.xml");
    saveConfigBIN(configtosave,"config.bin");

    ScoreCheckingConfig loadedconfig;
    this->config=new ScoreCheckingConfig();
    loadConfigBIN(*config, "config.bin");

    std::cout << "Loaded " << config->Name << std::endl;
    std::cout << "SCript" << std::endl << static_cast<ScriptScoreChecker*>(config->vecScoreCheckers->at(3))->getScript() << std::endl;
    //this->on_actionOpen_Config_triggered();
}
//Shows the preferences window
void MainWindow::on_actionConfiguration_Prefs_triggered()
{
    ConfigPropertiesWindow *confmenu= new ConfigPropertiesWindow(0,this->config);
    confmenu->show();
}
//Saves current config
void MainWindow::on_actionSave_Config_triggered()
{
    QString filename= QFileDialog::getSaveFileName(this, tr("Save Config"),0,tr("Binary Files (*.bin);;XML Files (*.xml)"));
    //
    QString suffix = QFileInfo(filename).suffix();
    if (QFileInfo(filename).suffix()=="bin")
    {
        saveConfigBIN(*config, filename.toStdString().c_str());
    }else if (QFileInfo(filename).suffix()=="xml")
    {
        saveConfigXML(*config, filename.toStdString().c_str());
    }

}

void MainWindow::on_actionOpen_Config_triggered()
{

    QString filename= QFileDialog::getOpenFileName(this, tr("Open Config"),0,tr("Binary Files (*.bin);;XML Files (*.xml)"));
    if (QFileInfo(filename).suffix()=="bin")
    {
        delete this->config;
        this->config=new ScoreCheckingConfig();
        loadConfigBIN(*config, filename.toStdString().c_str());
        scoringmodel= new MyScoringModel(this, config->vecScoreCheckers);
        scoringdelegate= new MyDelegate(this);
        this->SetupTable();
    }else if (QFileInfo(filename).suffix()=="xml")
    {
        delete this->config;
        this->config=new ScoreCheckingConfig();
        loadConfigXML(*config, filename.toStdString().c_str());
        scoringmodel= new MyScoringModel(this, config->vecScoreCheckers);
        scoringdelegate= new MyDelegate(this);
        this->SetupTable();
    }

}
void MainWindow::scoreupdate()
{
    std::cout << "Times up" << std::endl;
    config->GenerateScoreReport();
}

void MainWindow::on_actionTimer_Start_toggled(bool arg1)
{
    if (arg1){if (this->config->checkSeconds==0)this->config->checkSeconds=5;this->timer->start(this->config->checkSeconds*1000);}else{this->timer->stop();}
}

void MainWindow::on_actionNew_Config_triggered()
{
    if (true) //ask first before erasing
    {
        delete this->config;
        this->config=new ScoreCheckingConfig();
        scoringmodel= new MyScoringModel(this, config->vecScoreCheckers);
        scoringdelegate= new MyDelegate(this);
        this->SetupTable();
    }

}

void MainWindow::on_actionDelete_triggered()
{
    QItemSelectionModel *select = ui->mainTable->selectionModel();

    if (select->hasSelection())
    {
        //Removes selected scorecheckers via the model
        scoringmodel->removeCheckers(select->selectedRows());
    }
}
