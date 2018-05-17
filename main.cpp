#include "mainwindow.h"
#include "backgroundservice.h"
#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <signal.h>
#ifdef __linux__
void catchUnixSignals(std::initializer_list<int> quitSignals);
#endif
int main(int argc, char *argv[])
{
    #ifdef DONTRUN
    #define _WIN32_WINNT 0x0502
    #include <windows.h>
    if (AttachConsole(ATTACH_PARENT_PROCESS)) {
        freopen("CONOUT$", "w", stdout);
        freopen("CONOUT$", "w", stderr);
    }
    #endif
    if (argc>=2) //two or more arguments
    {
        if (std::string(argv[1])=="--background")
        {
            #ifdef __linux__
            catchUnixSignals({SIGQUIT, SIGINT, SIGTERM, SIGHUP});
            #endif
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
#ifdef __linux__
//catch a quit signal for ending gracefully
void catchUnixSignals(std::initializer_list<int> quitSignals) {
    auto handler = [](int sig) -> void {
        // blocking and not aysnc-signal-safe func are valid
        printf("\nquit the application by signal(%d).\n", sig);
        QCoreApplication::quit();
    };

    sigset_t blocking_mask;
    sigemptyset(&blocking_mask);
    for (auto sig : quitSignals)
        sigaddset(&blocking_mask, sig);

    struct sigaction sa;
    sa.sa_handler = handler;
    sa.sa_mask    = blocking_mask;
    sa.sa_flags   = 0;

    for (auto sig : quitSignals)
        sigaction(sig, &sa, nullptr);
}
#endif
