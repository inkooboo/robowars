#include "server_defs.hpp"

#include "logger.hpp"
#include "server.hpp"
#include "thread_pool.hpp"

#include "cpp_defs.hpp"
#include "shutdown_signal.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

int server_entry_point(int argc, char* argv[], shutdown_signal_t stopper)
{
    unused_param(argc);
    unused_param(argv);

    set_this_thread_log_name("server");

    srand((unsigned int)time(0));

    try
    {
        auto master = std::make_shared<master_t<server>>();

        master->add_managed_subsystem<thread_pool_t>();
        master->add_managed_subsystem<server_t>(std::ref(master->subsystem<thread_pool_t>().io_service()));

        master->start();

        while (!stopper.is_set())
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }

        master->stop();
    }
    catch (std::exception& e)
    {
        std::cerr << "Exception: " << e.what() << "\n";
        stopper.set();
    }

    return 0;
}
