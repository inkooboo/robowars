#include <QCoreApplication>

#include "server_defs.hpp"

#include "master.hpp"

#include "logger.hpp"
#include "server.hpp"
#include "thread_pool.hpp"
#include "command_processor.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    set_this_thread_log_name("server");

    srand((unsigned int)time(0));

    try
    {
        boost::asio::io_service io_svc;

        master_t master;
        master.add_managed_subsystem<thread_pool_t>(std::ref(io_svc));
        master.add_managed_subsystem<server_t>(std::ref(io_svc));
        master.add_managed_subsystem<command_processor_t>();

        master.start();

        master.stop();
    }
    catch (std::exception& e)
    {
        log<critical>() << "Exception: " << e.what() << "\n";
    }
    return a.exec();
}
