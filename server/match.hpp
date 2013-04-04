//
//  ai_base.hpp
//
//
//  Created by inkooboo on 4/4/13.
//
//

#ifndef MATCH_HPP
#  define MATCH_HPP

#  include "noncopyable.hpp"
#  include "session.hpp"
#  inlcude "field.hpp"

#  include <memory>

struct match_t : private noncopyable_t
{
    std::shared_ptr<session_t> client_session; //in future will be array of players sessions


    void on_time_chunk(float dt);
};

#endif // MATCH_HPP
