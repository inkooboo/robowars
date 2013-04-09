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
#  include "server_defs.hpp"

#  include <map>
#  include <mutex>
#  include <vector>

class field_t : private noncopyable_t
{
public:
    field_t();

    void on_time_chunk(float dt_ms);

    std::string xserver_field_dump();

private:
    game_object_set_t m_objects;
    std::mutex m_objects_guard;
};

#endif // FIELD_HPP
