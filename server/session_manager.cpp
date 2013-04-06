#include "session_manager.hpp"
#include "session.hpp"

#include <memory>

session_manager_t::session_manager_t(boost::asio::io_service &io_svc)
    : m_io_svc(io_svc)
{
}

void session_manager_t::start()
{
    log<debug>() << "starting";
}

void session_manager_t::stop()
{
    log<debug>() << "stopping";
}

session_ptr session_manager_t::create_session()
{
    session_ptr new_session = std::make_shared<session_t>(m_io_svc);

    log<debug>() << "created session " << new_session.get();

    std::lock_guard<std::mutex> lock(m_guard);
    m_sessions.insert(new_session);
    return new_session;
}

void session_manager_t::end_session(session_t *session)
{
    auto null_deleter = [](session_t *){};

    log<debug>() << "end session " << session;

    std::lock_guard<std::mutex> lock(m_guard);
    std::shared_ptr<session_t> shared(session, null_deleter);

    m_sessions.erase(shared);
}

