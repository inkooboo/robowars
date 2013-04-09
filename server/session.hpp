#ifndef _SESSION_HPP_
#  define _SESSION_HPP_

#  include "logger.hpp"
#  include "server_defs.hpp"

#  include "noncopyable.hpp"

#  include <json.h>
#  include <boost/asio.hpp>
#  include <memory>
#  include <atomic>

class session_t : private noncopyable_t, public std::enable_shared_from_this<session_t>
{
    ADD_CLASS_PREFIX_TO_LOG(session_t)
public:
    enum state_t
    {
          st_connected
        , st_authenticated
        , st_ready_for_game
        , st_in_game
    };

    session_t(boost::asio::io_service& io_service);
    ~session_t();

    void start_read();

    void send_message(const Json::Value &response);

    boost::asio::ip::tcp::socket & socket();
    user_info_ptr & user_info();
    state_t & state();
    std::atomic<bool> & valid();
    match_weak_ptr & match();

private:
    void handle_read(const boost::system::error_code& error, size_t bytes_transferred);

    void handle_write(const boost::system::error_code& error);

    boost::asio::ip::tcp::socket m_socket;
    const static int MAX_DATA_LENGTH = 8192;
    char m_data[MAX_DATA_LENGTH];

    user_info_ptr m_user_info;
    state_t m_state;

    std::atomic<bool> m_valid;

    match_weak_ptr m_match;
};

#endif //_SESSION_HPP_
