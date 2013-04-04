#ifndef SERVER_DEFS_HPP
#define SERVER_DEFS_HPP

#  include "cpp_defs.hpp"
#  include "noncopyable.hpp"

#  include "thread_pool.hpp"
#  include "server.hpp"

struct master_t : private noncopyable_t
{
    thread_pool_t thread_pool;
    server_t server;
};

inline master_t &master()
{

}

#endif // SERVER_DEFS_HPP
