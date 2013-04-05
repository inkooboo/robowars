#ifndef COMMAND_PROCESSOR_HPP
#  define COMMAND_PROCESSOR_HPP

#  include "server_defs.hpp"
#  include "subsystem.hpp"

#  include "noncopyable.hpp"

#  include <json.h>

class command_processor_t : public subsystem_t
{
public:
    command_processor_t();

    Json::Value process_command(session_ptr &session, const Json::Value &command);
};

#endif // COMMAND_PROCESSOR_HPP
