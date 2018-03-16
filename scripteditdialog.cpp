#include "scripteditdialog.h"
#include "ui_scripteditdialog.h"

ScriptEditDialog::ScriptEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScriptEditDialog)
{
    ui->setupUi(this);
    QFont f("unexistent");
    f.setStyleHint(QFont::Monospace);
    ui->txtScriptEdit->setFont(f);
}
ScriptEditDialog::ScriptEditDialog(QWidget *parent, std::string currentScript) :
    QDialog(parent),
    ui(new Ui::ScriptEditDialog)
{
    ui->setupUi(this);
    QFont f("unexistent");
    f.setStyleHint(QFont::Monospace);
    ui->txtScriptEdit->setFont(f);
    this->oldScript=currentScript;
    ui->txtScriptEdit->setPlainText(QString(this->oldScript.c_str()));

}
ScriptEditDialog::~ScriptEditDialog()
{
    delete ui;
}

void ScriptEditDialog::on_buttonBox_accepted()
{
    this->newScript=ui->txtScriptEdit->toPlainText().toStdString();

}
std::string ScriptEditDialog::getScript()
{
    return this->newScript;
}
