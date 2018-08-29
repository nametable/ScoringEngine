#include "playerdashboard.h"
#include "ui_playerdashboard.h"
#include "qradiobutton.h"
#include "qplaintextedit.h"
PlayerDashboard::PlayerDashboard(QWidget *parent, ScoreCheckingConfig *config) :
    QMainWindow(parent),
    ui(new Ui::PlayerDashboard)
{
    ui->setupUi(this);
    for (unsigned int i=0; i<10; i++){
        this->centralWidget()->layout()->addWidget(new QRadioButton(QString("Test Radio ")+ QString(std::to_string(i).c_str()),this));
        this->centralWidget()->layout()->addWidget(new QPlainTextEdit(QString("Test Plain Text Edit ")+ QString(std::to_string(i).c_str()),this));

    }

}

PlayerDashboard::~PlayerDashboard()
{
    delete ui;
}

