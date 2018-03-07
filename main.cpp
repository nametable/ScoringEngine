#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <string>
#include <QTimer>
void tick()
{

}
int main(int argc, char *argv[])
{
    if (argc==2)
    {
        if (std::string(argv[1])=="--background")
        {
            std::cout << "ScoringEngine background mode started...\n";
            QEventLoop loop();
            QTimer *timer=new QTimer();
            //connect(timer, SIGNAL(timeout()),0, SLOT(tick()));
            timer->start(1000);
            //QCoreApplication a(argc, argv);
            std::cout << "More Done??...\n";
            //return loop.exec();
            //return a.exec();
        }
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
