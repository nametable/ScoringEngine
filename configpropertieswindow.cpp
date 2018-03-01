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
    ui->txtName->setText(QString(this->config->Name.c_str()));
    ui->txtPassphrase->setText(QString(this->config->Passphrase.c_str()));
    ui->txtDescription->setText(QString(this->config->Description.c_str()));
    ui->spinSeconds->setValue(this->config->checkSeconds);
}

ConfigPropertiesWindow::~ConfigPropertiesWindow()
{
    delete ui;
}

void ConfigPropertiesWindow::on_buttonBox_accepted()
{
    this->config->Name=ui->txtName->text().toStdString();
    this->config->Passphrase=ui->txtPassphrase->text().toStdString();
    this->config->Description=ui->txtDescription->text().toStdString();
    this->config->checkSeconds=ui->spinSeconds->value();
}
