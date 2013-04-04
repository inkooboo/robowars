#ifndef MATCH_HPP
#  define MATCH_HPP

#  include "noncopyable.hpp"
#  include "session.hpp"

#  include <memory>

struct match_t : private noncopyable_t
{
    std::shared_ptr<session_t> client_session; //in future will be array of players sessions


};

#endif // MATCH_HPP
