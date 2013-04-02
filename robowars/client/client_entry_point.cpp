#include "client_defs.hpp"

#include "shutdown_flag.hpp"

#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <memory>

int client_entry_point(int argc, char *argv[], shutdown_signal_t &stopper)
{
    try
    {
        QApplication a(argc, argv);

        MainWindow main_window; // should be moved to render system
        main_window.show();     //

        auto master = std::make_shared<master_t<client>>();
        master->start();

        int result = a.exec();

        master->stop();

        return result;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        stopper.emitt();
    }

    return 0;
}