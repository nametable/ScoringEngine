#include "configpropertieswindow.h"
#include "ui_configpropertieswindow.h"

ConfigPropertiesWindow::ConfigPropertiesWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigPropertiesWindow)
{
    ui->setupUi(this);
}
ConfigPropertiesWindow::ConfigPropertiesWindow(QWidget *parent, ScoreCheckingConfig *config) :
    QDialog(parent),
    ui(new Ui::ConfigPropertiesWindow)
{
    this->config=config;
    ui->setupUi(this);
}

ConfigPropertiesWindow::~ConfigPropertiesWindow()
{
    delete ui;
}

void ConfigPropertiesWindow::on_buttonBox_accepted()
{

}
