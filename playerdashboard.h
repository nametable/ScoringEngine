#ifndef PLAYERDASHBOARD_H
#define PLAYERDASHBOARD_H

#include <QMainWindow>
#include "scorecheckingconfig.h"
namespace Ui {
class PlayerDashboard;
}

class PlayerDashboard : public QMainWindow
{
    Q_OBJECT

public:
    explicit PlayerDashboard(QWidget *parent = nullptr);
    explicit PlayerDashboard(QWidget *parent = nullptr, ScoreCheckingConfig *config=nullptr);
    ~PlayerDashboard();

private:
    Ui::PlayerDashboard *ui;
};

#endif // PLAYERDASHBOARD_H
