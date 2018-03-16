#ifndef SCRIPTEDITDIALOG_H
#define SCRIPTEDITDIALOG_H

#include <QDialog>

namespace Ui {
class ScriptEditDialog;
}

class ScriptEditDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ScriptEditDialog(QWidget *parent = 0);
    explicit ScriptEditDialog(QWidget *parent = 0, std::string currentScript="");
    ~ScriptEditDialog();
    std::string getScript();
private slots:
    void on_buttonBox_accepted();

private:
    Ui::ScriptEditDialog *ui;
    std::string oldScript;
    std::string newScript;
};

#endif // SCRIPTEDITDIALOG_H
