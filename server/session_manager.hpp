#ifndef SESSION_MANAGER_HPP
#  define SESSION_MANAGER_HPP

#  include "server_defs.hpp"
#  include "subsystem.hpp"
#  include "logger.hpp"

#  include <boost/asio.hpp>
#  include <mutex>
#  include <set>

class session_manager_t : public subsystem_t
{
    ADD_CLASS_PREFIX_TO_LOG(session_manager_t)

    void start() override;
    void stop() override;

public:
    session_manager_t(boost::asio::io_service &io_svc);

    session_ptr create_session();
    void end_session(session_t *session);

    boost::asio::io_service &m_io_svc;

    std::mutex m_guard;
    std::set<session_ptr> m_sessions;
};

#endif // SESSION_MANAGER_HPP
