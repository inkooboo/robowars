#ifndef MATCH_MANAGER_HPP
#  define MATCH_MANAGER_HPP

#  include "server_defs.hpp"
#  include "subsystem.hpp"
#  include "logger.hpp"
#  include "match.hpp"

#  include <boost/asio.hpp>
#  include "spinlock.hpp"

class match_manager_t : public subsystem_t
{
    ADD_CLASS_PREFIX_TO_LOG(match_manager_t)

    void start() override;
    void stop() override;

public:
    match_manager_t(boost::asio::io_service &io_svc);

    void add_match_ready_session(session_ptr &session);
    void remove_match_ready_session(session_ptr &session);

    void remove_match(match_ptr match);
private:

    void try_to_create_match();

    boost::asio::io_service &m_io_svc;

    session_set_t m_ready_sessions;
    spinlock_t m_session_guard;
    match_set_t m_matches;
    spinlock_t m_match_guard;
};

#endif // MATCH_MANAGER_HPP
