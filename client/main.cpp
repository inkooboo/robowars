#include "cpp_defs.hpp"

#include "master.hpp"
#include "logger.hpp"

#include "network.hpp"
#include "xserver.hpp"

#include <QApplication>

int main(int argc, char *argv[])
{
    srand((unsigned int)time(0));

    try
    {
        QApplication a(argc, argv);

        master_t master;

        master.add_managed_subsystem<network_t>();
        master.add_managed_subsystem<xserver_t>();

        a.exec();

        master.stop();
    }
    catch(std::exception& e)
    {
        log<critical>()<<"Exception: "<<e.what();
    }
}
