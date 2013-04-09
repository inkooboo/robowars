//
//  ai_base.hpp
//
//
//  Created by inkooboo on 4/4/13.
//
//

#ifndef MATCH_HPP
#  define MATCH_HPP

#  include "server_defs.hpp"
#  include "noncopyable.hpp"
#  include "logger.hpp"
#  include <boost/asio.hpp>
#  include <memory>
#  include <chrono>

class match_t : private noncopyable_t, public std::enable_shared_from_this<match_t>
{
    ADD_CLASS_PREFIX_TO_LOG(match_t)
public:
    match_t(const session_set_t &sessions, boost::asio::io_service &io_svc);
    ~match_t();

    void on_time_chunk();

    session_set_t & sessions();

    void start();
    void stop();

private:
    enum state_t
    {
          st_created
        , st_started
        , st_in_game
        , st_ending
    } m_state;


    boost::asio::io_service &m_io_svc;

    session_set_t m_sessions;

    field_ptr m_field;

    std::chrono::high_resolution_clock::time_point m_last_time;
    float m_xserver_message_time_ms;
};

#endif // MATCH_HPP
