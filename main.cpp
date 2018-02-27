#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <string>
int main(int argc, char *argv[])
{
    if (argc==2)
    {
        if (std::string(argv[1])=="--background")
        {
            std::cout << "ScoringEngine background mode started...\n";
            QCoreApplication a(argc, argv);
            return a.exec();
        }
    }

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
