#include "playerdashboard.h"
#include "ui_playerdashboard.h"
#include "qradiobutton.h"
PlayerDashboard::PlayerDashboard(QWidget *parent, ScoreCheckingConfig *config) :
    QMainWindow(parent),
    ui(new Ui::PlayerDashboard)
{
    ui->setupUi(this);
    for (unsigned int i=0; i<10; i++){
        this->centralWidget()->layout()->addWidget(new QRadioButton(QString("Test Radio ")+ QString(i),this));
    }

}

PlayerDashboard::~PlayerDashboard()
{
    delete ui;
}

