#include "server_defs.hpp"

#include "logger.hpp"
#include "server.hpp"
#include "thread_pool.hpp"

#include "cpp_defs.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>

int server_main(int argc, char* argv[])
{
    unused_param(argc);
    unused_param(argv);

    logger::set_thread_name("Main");

    srand((unsigned int)time(0));

    try
    {
        master_t<server> master;

        master.add_managed_subsystem<Logger>();
        master.add_managed_subsystem<ThreadPool>();
        master.add_managed_subsystem<Server>(std::ref(master.subsystem<ThreadPool>().get_io_service()));

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
