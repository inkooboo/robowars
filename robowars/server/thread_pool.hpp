#ifndef _THREAD_POOL_HPP_
# define _THREAD_POOL_HPP_

# include "subsystem.hpp"

# include "logger.hpp"

# include <thread>
# include <boost/asio.hpp>
# include <vector>
# include <iterator>
# include <sstream>

class ThreadPool : public subsystem_t
{
    virtual void start()
    {
        _work = new boost::asio::io_service::work(_svc);

        size_t threads = std::thread::hardware_concurrency() + 1;
        if (threads < 1)
        {
            threads = 2;
        }

        logger::log(TRACE) << "[Thread pool] Using " << threads << " threads";

        _threads.resize(threads - 1);

        size_t thr_name = 0;
        for (auto &i : _threads)
        {
            i = std::thread(&ThreadPool::worker_thread_func, this, thr_name++);
        }

    }

    virtual void stop()
    {
        delete _work;

        for (auto &i : _threads)
        {
            if (i.joinable())
            {
                i.join();
            }
        }

    }

public:

    void join_thread_pool()
    {
        logger::log(TRACE, "[Thread pool] Thread joined to thread pool");
        _svc.run();
    }

    boost::asio::io_service & get_io_service()
    {
        return _svc;
    }

private:

    void worker_thread_func(size_t n)
    {
        std::ostringstream name;
        name << n;
        logger::set_thread_name(name.str());
        join_thread_pool();
    }

    boost::asio::io_service _svc;
    boost::asio::io_service::work *_work;

    std::vector<std::thread> _threads;
};


#endif //_THREAD_POOL_HPP_
