#include "logger.hpp"
#include "server.hpp"
#include "thread_pool.hpp"

#include "server_defs.hpp"
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
