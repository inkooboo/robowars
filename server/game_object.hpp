//
//  ai_base.hpp
//
//
//  Created by inkooboo on 4/4/13.
//
//

#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#  include "noncopyable.hpp"

#  include "primitives.hpp"
#  include "server_defs.hpp"

#  include <string>

class game_object_t : private noncopyable_t
{
public:
    ai_base_ptr ai;
    
    size_t id;

    std::string type;

    float max_speed;

    vector3 position;
    vector3 direction;
};




#endif // GAME_OBJECT_HPP
