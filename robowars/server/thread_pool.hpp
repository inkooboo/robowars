#ifndef _THREAD_POOL_HPP_
#  define _THREAD_POOL_HPP_

#  include "subsystem.hpp"

#  include <boost/asio.hpp>

#  include <thread>
#  include <vector>
#  include <memory>

class thread_pool_t : public subsystem_t
{
    virtual void start();
    virtual void stop();

public:
    void join_thread_pool();
    boost::asio::io_service & io_service();

private:
    void worker_thread_func(size_t n);

    boost::asio::io_service m_svc;
    std::unique_ptr<boost::asio::io_service::work> m_work;

    std::vector<std::thread> m_threads;
};


#endif //_THREAD_POOL_HPP_
