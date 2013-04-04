#include "shutdown_signal.hpp"
#include "client_defs.hpp"

#include "mainwindow.h"
#include <QApplication>

#include <iostream>
#include <memory>

int client_entry_point(int argc, char *argv[], shutdown_signal_t stopper)
{
    try
    {
        QApplication a(argc, argv);

        MainWindow main_window; // should be moved to render system
        main_window.show();     //

        int result = a.exec();

        return result;
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        stopper.set();
    }

    return 0;
}
