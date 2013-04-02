#ifndef _SERVER_HPP_
# define _SERVER_HPP_

# include "master.hpp"
# include "session.hpp"

# include <boost/asio.hpp>

class Server: public subsystem_t
{
public:
    Server();

private:
    virtual void start();
    virtual void stop();

    void start_accept();

    void handle_accept(Session* new_session, const boost::system::error_code& error);

    boost::asio::io_service& io_service_;
    boost::asio::ip::tcp::acceptor acceptor_;
};

#endif //_SERVER_HPP_
