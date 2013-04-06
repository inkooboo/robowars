#ifndef _SESSION_HPP_
#  define _SESSION_HPP_

#  include "logger.hpp"
#  include "server_defs.hpp"

#  include "noncopyable.hpp"

#  include <json.h>
#  include <boost/asio.hpp>
#  include <memory>

class session_t : private noncopyable_t
{
    ADD_CLASS_PREFIX_TO_LOG(session_t)
public:
    enum state_t
    {
          st_connected
        , st_authenticated
        , st_in_game
    };

    static session_ptr create(boost::asio::io_service& io_service);
    void destroy();

    boost::asio::ip::tcp::socket& socket();

    void start_read();

    void send_message(const Json::Value &response);

    user_info_ptr & user_info();
    state_t & state();

private:
    session_t(boost::asio::io_service& io_service);

    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

    void handle_write(const boost::system::error_code& error);

    boost::asio::ip::tcp::socket m_socket;
    const static int MAX_DATA_LENGTH = 8192;
    char m_data[MAX_DATA_LENGTH];

    user_info_ptr m_user_info;
    state_t m_state;

    session_ptr m_this_ptr;
};

#endif //_SESSION_HPP_
