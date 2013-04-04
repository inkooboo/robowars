//
//  ai_base.hpp
//
//
//  Created by inkooboo on 4/4/13.
//
//

#ifndef FIELD_HPP
#define FIELD_HPP

#  include "noncopyable.hpp"
#  include "game_object.hpp"

#  include <map>

struct field_t : private noncopyable_t
{
    std::map<size_t, game_object_t> m_objects;
    
    void on_time_chunk(float dt);
};

#endif // FIELD_HPP
