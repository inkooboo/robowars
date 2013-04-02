#include "server.hpp"

#include "thread_pool.hpp"
#include "logger.hpp"

# include <boost/bind.hpp>

static const int s_port = 4576;

Server::Server()
    : io_service_(master_t::subsystem<ThreadPool>().get_io_service())
    , acceptor_(io_service_, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), s_port))
{
    logger::log(TRACE) << "[Server] Create server using port " << s_port;
}

void Server::start()
{
    logger::log(TRACE, "[Server] Start server");
    start_accept();
}

void Server::stop()
{
}

void Server::start_accept()
{
    Session* new_session = new Session(io_service_);
    acceptor_.async_accept(new_session->socket(), boost::bind(&Server::handle_accept, this, new_session, boost::asio::placeholders::error));
}

void Server::handle_accept(Session* new_session, const boost::system::error_code& error)
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
