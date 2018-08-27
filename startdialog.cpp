#include "startdialog.h"
#include "ui_startdialog.h"
#include "version.h"

StartDialog::StartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startdialog)
{
    ui->setupUi(this);
    //Display version number
    ui->labelInfo->setText(QString(std::string("ScoringEngine\nCopyright " + std::to_string(VERSION_YEAR) + " by Logan Bateman\nVersion " + std::to_string(VERSION_MAJOR) + "." + std::to_string(VERSION_MINOR) + "." + std::to_string(VERSION_PATCH)).c_str()));
}

StartDialog::~StartDialog()
{
    delete ui;
}

void StartDialog::on_btnSingle_clicked()
{

}

void StartDialog::on_btnMulti_clicked()
{

}

void StartDialog::on_btnEditor_clicked()
{
    this->hide();
    this->editorWindow= new MainWindow(this);
    this->editorWindow->show();
}
