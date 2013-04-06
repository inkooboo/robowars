#ifndef _SERVER_HPP_
# define _SERVER_HPP_

#  include "logger.hpp"
#  include "server_defs.hpp"
#  include "subsystem.hpp"

#  include <boost/asio.hpp>

class server_t : public subsystem_t
{
    ADD_CLASS_PREFIX_TO_LOG(server_t)

    void start() override;
    void stop() override;

public:
    server_t(boost::asio::io_service &io_svc);

private:
    void start_accept();

    void handle_accept(session_ptr &new_session, const boost::system::error_code& error);

    boost::asio::io_service& m_io_svc;
    boost::asio::ip::tcp::acceptor m_acceptor;
};

#endif //_SERVER_HPP_
