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

    //confmen
    statusBar()->showMessage("Program loaded.");
    //RunCommandScoreChecker testcheck;
    //testcheck.setCommand("ls");
    //testcheck.executeCommand();
    //std::cout << testcheck.getCommandOutput();
    TestScoreCheckers();

    //config= new ScoreCheckingConfig;
    //config->vecScoreCheckers->push_back(new PathExistScoreChecker());
    //config->vecScoreCheckers->push_back(new PathExistScoreChecker());
    //config->vecScoreCheckers->push_back(new EmptyScoreChecker());
    scoringmodel= new MyScoringModel(this, config->vecScoreCheckers);
    scoringdelegate= new MyDelegate(this);
    //scoringmodel->set
    SetupTable();

    timer= new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(scoreupdate())); //tell timer to execute scoreupdate()


}
void MainWindow::SetupTable()
{
    ui->mainTable->setModel(scoringmodel); //scoringmodel);
    ui->mainTable->setItemDelegate(scoringdelegate);
    //ui->mainTable->setEditTriggers(QAbstractItemView::AllEditTriggers);
    QHeaderView *verticalHeader = ui->mainTable->verticalHeader();
    verticalHeader->setSectionResizeMode(QHeaderView::Fixed);
    verticalHeader->setDefaultSectionSize(30);
    QHeaderView *horizontalHeader = ui->mainTable->horizontalHeader();
    //horizontalHeader->setSectionResizeMode(QHeaderView::Fixed);
    horizontalHeader->setDefaultSectionSize(60);
    //ui->mainTable->setHorizontalHeader(QHeaderView());
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
    //this->ui->mainTable->dataChanged(this->scoringmodel->index(this->config->vecScoreCheckers->size()-1, 0, QModelIndex()),this->scoringmodel->index(this->config->vecScoreCheckers->size()-1, 6, QModelIndex()));
    //this->config->vecScoreCheckers->push_back(new EmptyScoreChecker());
    //scoringmodel->refresh(this->config->vecScoreCheckers->size()-1);
    scoringmodel->insertChecker(new EmptyScoreChecker());
}
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
    this->on_actionOpen_Config_triggered();
}

void MainWindow::on_actionConfiguration_Prefs_triggered()
{
    ConfigPropertiesWindow *confmenu= new ConfigPropertiesWindow(0,this->config);
    confmenu->show();
}

void MainWindow::on_actionSave_Config_triggered()
{
    QFileDialog savedialog(0, tr("Save Config"));

    QString filename=savedialog.getSaveFileName(0,tr("Save Config"),tr("*.bin"));
    saveConfigBIN(*config, filename.toStdString().c_str());
}

void MainWindow::on_actionOpen_Config_triggered()
{
    QFileDialog opendialog(0, tr("Open Config"));

    QString filename=opendialog.getOpenFileName(0,tr("Open Config"),tr("*.bin"));
    delete this->config;
    this->config=new ScoreCheckingConfig();
    loadConfigBIN(*config, filename.toStdString().c_str());
    scoringmodel= new MyScoringModel(this, config->vecScoreCheckers);
    scoringdelegate= new MyDelegate(this);
    this->SetupTable();
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
