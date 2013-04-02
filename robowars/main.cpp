/// Common entry point for both client and server run

#include <thread>
#include <iostream>

#include "shutdown_signal.hpp"

extern entry_point_t server_entry_point;
extern entry_point_t client_entry_point;

int main(int argc, char* argv[])
{
    try
    {
        shutdown_signal_t stopper;

        std::thread server(server_entry_point, argc, argv, stopper);

        client_entry_point(argc, argv, stopper);

        stopper.set();

        server.join();
    }
    catch(std::exception &e)
    {
        std::cout << "exception in common entry point: " << e.what();
    }
}

