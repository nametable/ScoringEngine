#include "mainwindow.h"
#include "backgroundservice.h"
#include <iostream>
#include <string>
void tick()
{

}
int main(int argc, char *argv[])
{
    if (argc>=2) //two or more arguments
    {
        if (std::string(argv[1])=="--background")
        {
            BackgroundService bkserv(argc,argv);
            bkserv.LoadConfig("config.bin");
            bkserv.Run();
            return 0;
        }
    }
    //No arguments -- assume GUI
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
