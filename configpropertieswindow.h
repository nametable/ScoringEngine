#ifndef CONFIGPROPERTIESWINDOW_H
#define CONFIGPROPERTIESWINDOW_H

#include <QDialog>
#include "scorecheckingconfig.h"
namespace Ui {
class ConfigPropertiesWindow;
}

class ConfigPropertiesWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigPropertiesWindow(QWidget *parent = 0);
    explicit ConfigPropertiesWindow(QWidget *parent = 0, ScoreCheckingConfig *config=0);
    ~ConfigPropertiesWindow();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::ConfigPropertiesWindow *ui;
    ScoreCheckingConfig *config;
};

#endif // CONFIGPROPERTIESWINDOW_H
