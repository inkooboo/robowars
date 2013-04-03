#include "thread_pool.hpp"

#  include "logger.hpp"
#  include <string>

void thread_pool_t::start()
{
    m_work.reset(new boost::asio::io_service::work(m_svc));

    size_t threads = std::thread::hardware_concurrency() + 1;

    log<trace>() << "[Thread pool] Using " << threads << " threads";

    m_threads.resize(threads);

    size_t thr_name = 0;
    for (auto &i : m_threads)
    {
        i = std::thread(&thread_pool_t::worker_thread_func, this, thr_name++);
    }

}

void thread_pool_t::stop()
{
    m_work.reset();

    m_svc.stop();

    for (auto &i : m_threads)
    {
        if (i.joinable())
        {
            i.join();
        }
    }

}

void thread_pool_t::join_thread_pool()
{
    log<trace>() << "[Thread pool] Thread joined to thread pool:" << get_this_thread_log_name();
    m_svc.run();
}

boost::asio::io_service & thread_pool_t::io_service()
{
    return m_svc;
}

void thread_pool_t::worker_thread_func(size_t n)
{
    set_this_thread_log_name(std::to_string(n).c_str());
    join_thread_pool();
}

