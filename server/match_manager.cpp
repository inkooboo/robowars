#include "match_manager.hpp"

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
}

void match_manager_t::add_match_ready_session(session_ptr &session)
{

}

void match_manager_t::remove_match_ready_session(session_ptr &session)
{

}

void match_manager_t::try_to_create_match()
{

}
