#include "backgroundservice.h"

BackgroundService::BackgroundService(int argc, char *argv[], QObject *parent) : QObject(parent)
{

    this->runningconfig=new ScoreCheckingConfig; //create an instance of ScoreCheckingConfig
    this->app= new QCoreApplication(argc,argv);
}
BackgroundService::~BackgroundService()
{
    this->saveonexit();
}
void BackgroundService::LoadConfig(std::string configpath)
{
    loadConfigBIN(*this->runningconfig, configpath.c_str());
}
void BackgroundService::Run()
{

    std::cout << "ScoringEngine background mode started...\n";
    this->setup();
    this->app->exec();
}
void BackgroundService::mainloop()
{
    //std::cout << "More Done??...\n";
    this->curtime=std::chrono::system_clock::now();
    this->runningconfig->GenerateScoreReport();
}
void BackgroundService::setup()
{
    this->timer=new QTimer();
    connect(timer, SIGNAL(timeout()),this, SLOT(mainloop()));
    if (this->runningconfig->checkSeconds<1)this->runningconfig->checkSeconds=30;
    timer->start(this->runningconfig->checkSeconds*1000);
}
void BackgroundService::saveonexit()
{
    saveConfigBIN(*this->runningconfig, "config.bin");
}
