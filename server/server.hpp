#ifndef _SERVER_HPP_
# define _SERVER_HPP_

#  include "session.hpp"
#  include "logger.hpp"

#  include "subsystem.hpp"

#  include <boost/asio.hpp>

class server_t : public subsystem_t
{
    DEFINE_LOGGER_FOR_CLASS(server_t)

    virtual void start();
    virtual void stop();

public:
    server_t(boost::asio::io_service &io_svc);

private:
    void start_accept();

    void handle_accept(session_t* new_session, const boost::system::error_code& error);

    boost::asio::io_service& m_io_svc;
    boost::asio::ip::tcp::acceptor m_acceptor;
};

#endif //_SERVER_HPP_
