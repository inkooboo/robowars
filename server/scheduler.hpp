#ifndef SCHEDULER_HPP
#  define SCHEDULER_HPP

#  include "server_defs.hpp"
#  include "subsystem.hpp"
#  include "logger.hpp"

#  include <boost/asio.hpp>

class scheduler_t : public subsystem_t
{
    ADD_CLASS_PREFIX_TO_LOG(scheduler_t)

    void start() override;
    void stop() override;

public:
    scheduler_t(boost::asio::io_service &io_svc);

    void schedule(handler_t func, size_t delay_ms = 0);

private:
    void timer_handler(std::shared_ptr<boost::asio::deadline_timer> timer_holder, handler_t func, const boost::system::error_code& error);

    boost::asio::io_service &m_io_svc;
};

#endif // SCHEDULER_HPP
