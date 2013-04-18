#include "network.hpp"

#  include "common_defs.hpp"

static const char* host = "localhost";

network_t::network_t()
{
}

void network_t::start()
{
    connection_.connect("localhost", ROBOWARS_PORT);
}

void network_t::stop()
{
    connection_.disconnect();
}


void network_t::send(const std::vector<char> &data)
{
    connection_.send(data);
}

