#ifndef SCRIPTEDITDIALOG_H
#define SCRIPTEDITDIALOG_H

#include <QDialog>
#include "scriptscorechecker.h"
namespace Ui {
class ScriptEditDialog;
}

class ScriptEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScriptEditDialog(QWidget *parent = 0);
    explicit ScriptEditDialog(QWidget *parent = 0, std::string currentScript="");
    explicit ScriptEditDialog(QWidget *parent = 0, ScriptScoreChecker * scorechecker=0);
    ~ScriptEditDialog();
    std::string getScript();
    std::string getExtension();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::ScriptEditDialog *ui;
    std::string oldScript;
    std::string newScript;
    ScriptScoreChecker * scorechecker;
};

#endif // SCRIPTEDITDIALOG_H
