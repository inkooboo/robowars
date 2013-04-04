//
//  ai_base.hpp
//
//
//  Created by inkooboo on 4/4/13.
//
//

#ifndef SERVER_DEFS_HPP
#  define SERVER_DEFS_HPP

#  include "cpp_defs.hpp"

#  include <memory>

class game_object_t;
typedef std::shared_ptr<game_object_t> game_object_ptr;

class ai_base_t;
typedef std::shared_ptr<ai_base_t> ai_base_ptr;

#endif // SERVER_DEFS_HPP
