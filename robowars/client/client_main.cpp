#include "client_defs.hpp"

#include "mainwindow.h"
#include <QApplication>

int client_main(int argc, char *argv[])
{
    master_t<client> master;

    master.start();

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    
    master.stop();

    return a.exec();
}
