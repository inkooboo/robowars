/// Common entry point for both client and server run

#include <thread>
#include <iostream>

extern int server_main(int, char*[]);
extern int client_main(int, char*[]);

int main(int argc, char* argv[])
{
    try
    {
        std::thread server(server_main, argc, argv);

        client_main(argc, argv);

//        server.
        server.join();
    }
    catch(std::exception &e)
    {
        std::cout << "exception in common entry point: " << e.what();
    }
}

