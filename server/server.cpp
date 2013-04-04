#include "server.hpp"

#include "master.hpp"
#include "thread_pool.hpp"
#include "logger.hpp"

#include <boost/bind.hpp>

static const int s_port = 4576;

server_t::server_t(boost::asio::io_service &io_svc)
    : m_io_svc(io_svc)
    , m_acceptor(io_svc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), s_port))
{
    log<trace>() << "create server using port " << s_port;
}

void server_t::start()
{
    log<trace>() << "start server";
    start_accept();
}

void server_t::stop()
{
}

void server_t::start_accept()
{
    session_t* new_session = new session_t(m_io_svc);
    m_acceptor.async_accept(new_session->socket(), boost::bind(&server_t::handle_accept, this, new_session, boost::asio::placeholders::error));
}

void server_t::handle_accept(session_t *new_session, const boost::system::error_code& error)
{
    if (!error)
    {
        new_session->start_read();
    }
    else
    {
        delete new_session;
    }

    start_accept();
}