#include "scripteditdialog.h"
#include "ui_scripteditdialog.h"
#include "QComboBox"
ScriptEditDialog::ScriptEditDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ScriptEditDialog)
{
    ui->setupUi(this);
    QFont f("unexistent");
    f.setStyleHint(QFont::Monospace);
    ui->txtScriptEdit->setFont(f);
}
ScriptEditDialog::ScriptEditDialog(QWidget *parent, ScriptScoreChecker * scorechecker) :
    QDialog(parent),
    ui(new Ui::ScriptEditDialog)
{
    ui->setupUi(this);
    this->scorechecker=scorechecker;
    QFont f("unexistent");
    f.setStyleHint(QFont::Monospace);
    ui->txtScriptEdit->setFont(f);
    this->oldScript=scorechecker->getScript();
    ui->txtScriptEdit->setPlainText(QString(this->oldScript.c_str()));
    if (this->scorechecker->getScriptExtension()==".sh")ui->extCombo->setCurrentIndex(0);
    else if (this->scorechecker->getScriptExtension()==".bat")ui->extCombo->setCurrentIndex(1);
    else if (this->scorechecker->getScriptExtension()==".ps1")ui->extCombo->setCurrentIndex(2);
}
ScriptEditDialog::~ScriptEditDialog()
{
    delete ui;
}

void ScriptEditDialog::on_buttonBox_accepted()
{
    this->newScript=ui->txtScriptEdit->toPlainText().toStdString();
    this->scorechecker->setScript(this->newScript);
    this->scorechecker->setScriptExtension(this->getExtension());
}
std::string ScriptEditDialog::getScript()
{
    return this->newScript;
}
std::string ScriptEditDialog::getExtension()
{
    int index=ui->extCombo->currentIndex();
    switch (index) {
    case 0:
        return ".sh";
    case 1:
        return ".bat";
    case 2:
        return ".ps1";
    default:
        break;
    }
}
