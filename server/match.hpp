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
#  include "field.hpp"

#  include <boost/asio.hpp>

class match_t : private noncopyable_t
{
public:
    match_t(const session_set_t &sessions, boost::asio::io_service &io_svc);

    void on_time_chunk();

    session_set_t & sessions();

private:
    boost::asio::io_service &m_io_svc;

    session_set_t m_sessions;
};

#endif // MATCH_HPP
