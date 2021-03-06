#ifndef COMMANDS_HPP
#  define COMMANDS_HPP

#  include "noncopyable.hpp"
#  include "server_defs.hpp"

#  include <json.h>
#  include <string>

class packet_iface_t : private noncopyable_t
{
public:
    virtual ~packet_iface_t() {}
    virtual Json::Value process(session_ptr &session, const Json::Value &request) = 0;
};

commands_map_t get_commands_map();

#endif // COMMANDS_HPP
