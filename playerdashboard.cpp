#include "playerdashboard.h"
#include "ui_playerdashboard.h"
#include "qradiobutton.h"
PlayerDashboard::PlayerDashboard(QWidget *parent, ScoreCheckingConfig *config) :
    QMainWindow(parent),
    ui(new Ui::PlayerDashboard)
{
    ui->setupUi(this);
    this->centralWidget()->layout()->addWidget(new QRadioButton("Test Radio",this));
}

PlayerDashboard::~PlayerDashboard()
{
    delete ui;
}

