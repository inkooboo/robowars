#include "scheduler.hpp"

scheduler_t::scheduler_t(boost::asio::io_service &io_svc)
    : m_io_svc(io_svc)
{
}

void scheduler_t::start()
{
    log<debug>() << "starting";
}

void scheduler_t::stop()
{
    log<debug>() << "stopping";
}

void scheduler_t::schedule(handler_t func, size_t delay_ms)
{
    if (0 == delay_ms)
    {
        m_io_svc.post(func);
        return;
    }

    auto timer_ptr = std::make_shared<boost::asio::deadline_timer>(m_io_svc);
    timer_ptr->expires_from_now(boost::posix_time::milliseconds(delay_ms));
    timer_ptr->async_wait(std::bind(&scheduler_t::timer_handler, this, timer_ptr, func, std::placeholders::_1));
}

void scheduler_t::timer_handler(std::shared_ptr<boost::asio::deadline_timer> timer_holder, handler_t func, const boost::system::error_code& error)
{
    unused_params(timer_holder, error);
    m_io_svc.post(func);
}
