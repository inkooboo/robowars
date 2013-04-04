#ifndef FIELD_HPP
#define FIELD_HPP

#  include "noncopyable.hpp"
#  include "game_object.hpp"

#  include <map>

struct field_t : private noncopyable_t
{
    std::map<size_t, game_object_t
};

#endif // FIELD_HPP
