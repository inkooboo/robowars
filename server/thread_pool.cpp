#include "thread_pool.hpp"

#  include "logger.hpp"
#  include <string>

thread_pool_t::thread_pool_t(boost::asio::io_service &io_svc)
    : m_io_svc(io_svc)
{

}

void thread_pool_t::start()
{
    log<debug>() << "starting";

    m_work.reset(new boost::asio::io_service::work(m_io_svc));

    size_t threads = std::thread::hardware_concurrency() + 1;

    log<trace>() << "using " << threads << " threads";

    m_threads.resize(threads);

    size_t thr_name = 0;
    for (auto &i : m_threads)
    {
        i = std::thread(&thread_pool_t::worker_thread_func, this, thr_name++);
    }

}

void thread_pool_t::stop()
{
    log<debug>() << "stopping";

    m_work.reset();

    m_io_svc.stop();

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
    log<trace>() << "thread joined to thread pool:" << get_this_thread_log_name();
    m_io_svc.run();
}

void thread_pool_t::worker_thread_func(size_t n)
{
    set_this_thread_log_name((std::string("wrk") + std::to_string(n)).c_str());
    join_thread_pool();
}

