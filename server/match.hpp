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
#  inlcude "field.hpp"

#  include <memory>

class match_t : private noncopyable_t
{
public:
    session_ptr session; //in future will be array of players sessions


    void on_time_chunk(float dt);
};

#endif // MATCH_HPP
