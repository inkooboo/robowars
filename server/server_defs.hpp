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
#  include <unordered_map>
#  include <set>

#  ifdef DEBUG
#    define DEBUG_PROTO 1
#  endif

const static size_t COMMANDS_MAP_BUCKETS_COUNT = 1024;

class game_object_t;
typedef std::shared_ptr<game_object_t> game_object_ptr;

class ai_base_t;
typedef std::shared_ptr<ai_base_t> ai_base_ptr;

class user_info_t;
typedef std::shared_ptr<user_info_t> user_info_ptr;

class session_t;
typedef std::shared_ptr<session_t> session_ptr;
typedef std::set<session_ptr> session_set_t;

class command_processor_t;
typedef std::shared_ptr<command_processor_t> command_processor_ptr;

class command_iface_t;
typedef std::shared_ptr<command_iface_t> command_iface_ptr;
typedef std::unordered_map<std::string, command_iface_ptr> commands_map_t;

class match_t;
typedef std::shared_ptr<match_t> match_ptr;
typedef std::weak_ptr<match_t> match_weak_ptr;
typedef std::set<match_ptr> match_set_t;

#endif // SERVER_DEFS_HPP
