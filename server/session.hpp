#ifndef _SESSION_HPP_
#  define _SESSION_HPP_

#  include "logger.hpp"
#  include "server_defs.hpp"

#  include "noncopyable.hpp"

#  include <json.h>
#  include <boost/asio.hpp>
#  include <memory>

class session_t : private noncopyable_t, public std::enable_shared_from_this<session_t>
{
    ADD_CLASS_PREFIX_TO_LOG(session_t)
public:
    enum state_t
    {
          st_connected
        , st_authenticated
        , st_in_game
    };

    session_t(boost::asio::io_service& io_service);

    boost::asio::ip::tcp::socket& socket();

    void start_read();

    void send_message(const Json::Value &response);

    state_t state();
private:
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

    void handle_write(const boost::system::error_code& error);

    boost::asio::ip::tcp::socket m_socket;
    const static int MAX_DATA_LENGTH = 8192;
    char m_data[MAX_DATA_LENGTH];

    user_info_ptr m_user_info;

    state_t m_state;
};

#endif //_SESSION_HPP_
