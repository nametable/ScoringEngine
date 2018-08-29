#include "playerdashboard.h"
#include "ui_playerdashboard.h"

PlayerDashboard::PlayerDashboard(QWidget *parent, ScoreCheckingConfig *config) :
    QMainWindow(parent),
    ui(new Ui::PlayerDashboard)
{
    ui->setupUi(this);
    //this->add
}

PlayerDashboard::~PlayerDashboard()
{
    delete ui;
}

