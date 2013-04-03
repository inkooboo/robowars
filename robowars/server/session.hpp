#ifndef _SESSION_HPP_
#  define _SESSION_HPP_

#  include "logger.hpp"

#  include <boost/asio.hpp>

class session_t
{
    DEFINE_LOGGER_FOR_CLASS(session_t)
public:
    session_t(boost::asio::io_service& io_service);

    boost::asio::ip::tcp::socket& socket();

    void start_read();

//    void send_event(const Event &evt);

private:
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

    void handle_write(const boost::system::error_code& error);

    boost::asio::ip::tcp::socket m_socket;
    const static int MAX_DATA_LENGTH = 8192;
    char m_data[MAX_DATA_LENGTH];
};

#endif //_SESSION_HPP_
