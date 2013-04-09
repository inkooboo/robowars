#include "server_defs.hpp"
#include "cpp_defs.hpp"

#include "master.hpp"

#include "logger.hpp"
#include "server.hpp"
#include "thread_pool.hpp"
#include "command_processor.hpp"
#include "session_manager.hpp"
#include "match_manager.hpp"
#include "scheduler.hpp"

#include <cstdlib>
#include <ctime>
#include <iostream>
#include <memory>

int main(int argc, char *argv[])
{
    unused_params(argc, argv);

#ifdef DEBUG
    set_strict_threaded_log_output(true);
#endif
    set_this_thread_log_name("main");

    srand((unsigned int)time(0));

    try
    {
        boost::asio::io_service io_svc;

        master_t master;
        master.add_managed_subsystem<thread_pool_t>(std::ref(io_svc));
        master.add_managed_subsystem<server_t>(std::ref(io_svc));
        master.add_managed_subsystem<command_processor_t>();
        master.add_managed_subsystem<session_manager_t>(std::ref(io_svc));
        master.add_managed_subsystem<match_manager_t>(std::ref(io_svc));
        master.add_managed_subsystem<scheduler_t>(std::ref(io_svc));

        master.start();

        master.subsystem<thread_pool_t>().join_thread_pool();

        master.stop();
    }
    catch (std::exception& e)
    {
        log<critical>() << "Exception: " << e.what() << "\n";
    }

    return 0;
}
