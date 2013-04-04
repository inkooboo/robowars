#ifndef _THREAD_POOL_HPP_
#  define _THREAD_POOL_HPP_

#  include "logger.hpp"
#  include <boost/asio.hpp>

#  include "subsystem.hpp"

#  include <thread>
#  include <vector>
#  include <memory>

class thread_pool_t : public subsystem_t
{
    DEFINE_LOGGER_FOR_CLASS(thread_pool_t)

    virtual void start();
    virtual void stop();

public:
    thread_pool_t(boost::asio::io_service &io_svc);

    void join_thread_pool();

private:
    void worker_thread_func(size_t n);

    boost::asio::io_service& m_io_svc;
    std::unique_ptr<boost::asio::io_service::work> m_work;

    std::vector<std::thread> m_threads;
};


#endif //_THREAD_POOL_HPP_
