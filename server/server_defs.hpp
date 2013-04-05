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

#  define DEBUG_PROTO 1

const static size_t COMMANDS_MAP_BUCKETS_COUNT = 1024;

class game_object_t;
typedef std::shared_ptr<game_object_t> game_object_ptr;

class ai_base_t;
typedef std::shared_ptr<ai_base_t> ai_base_ptr;

class user_info_t;
typedef std::shared_ptr<user_info_t> user_info_ptr;

class session_t;
typedef std::shared_ptr<session_t> session_ptr;

class command_processor_t;
typedef std::shared_ptr<command_processor_t> command_processor_ptr;

class command_iface_t;
typedef std::shared_ptr<command_iface_t> command_iface_ptr;
typedef std::unordered_map<std::string, command_iface_ptr> commands_map_t;

#endif // SERVER_DEFS_HPP
