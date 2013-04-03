#ifndef _SERVER_HPP_
# define _SERVER_HPP_

# include "subsystem.hpp"
# include "session.hpp"

# include <boost/asio.hpp>

class server_t : public subsystem_t
{
public:
    server_t(boost::asio::io_service &io_svc);

private:
    virtual void start();
    virtual void stop();

    void start_accept();

    void handle_accept(Session* new_session, const boost::system::error_code& error);

    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
};

#endif //_SERVER_HPP_
