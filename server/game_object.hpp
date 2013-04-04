#ifndef GAME_OBJECT_HPP
#define GAME_OBJECT_HPP

#  include "noncopyable.hpp"

#  include "primitives.hpp"

#  include <string>
#  include <memory>

struct game_object_t : private noncopyable_t
{
    size_t id;

    std::string type;

    float max_speed;

    vector3 position;
    vector3 direction;
};

typedef std::shared_ptr<game_object_t> game_object_ptr;


#endif // GAME_OBJECT_HPP
