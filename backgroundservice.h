#ifndef BACKGROUNDSERVICE_H
#define BACKGROUNDSERVICE_H

#include <string>
#include <chrono>
#include <ctime>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <QTimer>
#include <QApplication>
#include <QSocketNotifier>
#include "scorecheckingconfig.h"
class BackgroundService : public QObject
{
    Q_OBJECT
public:
    void LoadConfig(std::string configpath);
    void Run();
    explicit BackgroundService(int argc, char *argv[], QObject *parent = nullptr);
    ~BackgroundService();
private:
    void setup();
    void saveonexit();
    ScoreCheckingConfig *runningconfig;
    QCoreApplication *app;
    QTimer *timer;
    std::chrono::system_clock::time_point curtime;

private slots:
    void mainloop();
};

#endif // BACKGROUNDSERVICE_H
