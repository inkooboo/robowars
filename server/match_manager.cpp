#include "match_manager.hpp"
#include "session.hpp"
#include <mutex>

match_manager_t::match_manager_t(boost::asio::io_service &io_svc)
    : m_io_svc(io_svc)
{
}

void match_manager_t::start()
{
    log<debug>() << "starting";
}

void match_manager_t::stop()
{
    log<debug>() << "stopping";
    std::lock_guard<spinlock_t> lock(m_match_guard);

    for (auto &m : m_matches)
    {
        m->stop();
    }
}

void match_manager_t::add_match_ready_session(session_ptr &session)
{
    {
        std::lock_guard<spinlock_t> lock(m_session_guard);
        m_ready_sessions.insert(session);
    }

    try_to_create_match();
}

void match_manager_t::remove_match_ready_session(session_ptr &session)
{
    std::lock_guard<spinlock_t> lock(m_session_guard);
    m_ready_sessions.erase(session);
}

void match_manager_t::try_to_create_match()
{
    // create match with one player
    session_set_t match_sessions;
    {
        std::lock_guard<spinlock_t> lock(m_session_guard);
        if (!m_ready_sessions.empty())
        {
            match_sessions.insert(*m_ready_sessions.begin());
            m_ready_sessions.erase(m_ready_sessions.begin());
        }
    }

    if (match_sessions.empty())
    {
        return;
    }

    match_ptr match = std::make_shared<match_t>(match_sessions, m_io_svc);

    for (auto &s : match_sessions)
    {
        s->match() = match;
    }

    {
        std::lock_guard<spinlock_t> lock(m_match_guard);
        m_matches.insert(match);
    }

    match->start();
}
