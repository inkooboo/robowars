#include "master.hpp"
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
    unused_params(argc, argv);

    set_this_thread_log_name("server");

    srand((unsigned int)time(0));

    try
    {
        struct master_t : private noncopyable_t
        {
            DEFINE_SUBSYSTEM(thread_pool_t, thread_pool)
            DEFINE_SUBSYSTEM(server_t, server)
        };

        master_t master;
//        master->add_managed_subsystem<thread_pool_t>();
//        master->add_managed_subsystem<server_t>(std::ref(master->subsystem<thread_pool_t>().io_service()));

        while (!stopper.is_set())
        {
            std::this_thread::sleep_for(std::chrono::seconds(1));
        }
    }
    catch (std::exception& e)
    {
        log<critical>() << "Exception: " << e.what() << "\n";
        stopper.set();
    }

    return 0;
}
