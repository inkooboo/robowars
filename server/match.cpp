#include "match.hpp"

match_t::match_t(const session_set_t &sessions, boost::asio::io_service &io_svc)
    : m_io_svc(io_svc)
    , m_sessions(sessions)
{

}

void match_t::on_time_chunk()
{

}

session_set_t & match_t::sessions()
{
    return m_sessions;
}



