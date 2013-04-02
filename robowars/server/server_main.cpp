#include "master.hpp"

#include "logger.hpp"
#include "server.hpp"
#include "thread_pool.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int server_main(int argc, char* argv[])
{
    logger::set_thread_name("Main");

    srand((unsigned int)time(0));

    try
    {
        master_t master;

        master.add_managed_subsystem<Logger>();
        master.add_managed_subsystem<ThreadPool>();
        master.add_managed_subsystem<Server>();

        master.start();

        master.subsystem<ThreadPool>().join_thread_pool();

        master.stop();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
    }

    return 0;
}
