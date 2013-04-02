#include "server_defs.hpp"

#include "logger.hpp"
#include "server.hpp"
#include "thread_pool.hpp"

#include "cpp_defs.hpp"
#include "shutdown_flag.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

int server_entry_point(int argc, char* argv[], shutdown_signal_t &stopper)
{
    unused_param(argc);
    unused_param(argv);

    set_this_thread_log_name("Main");

    srand((unsigned int)time(0));

    try
    {
        auto master = std::make_shared<master_t<server>>();

        master->add_managed_subsystem<ThreadPool>();
        master->add_managed_subsystem<Server>(std::ref(master->subsystem<ThreadPool>().get_io_service()));

        master->start();

        stopper.subscribe(std::bind(&master_t<server>::stop, master));

        master->subsystem<ThreadPool>().join_thread_pool();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        stopper.emitt();
    }

    return 0;
}
