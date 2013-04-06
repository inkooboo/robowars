#ifndef COMMAND_PROCESSOR_HPP
#  define COMMAND_PROCESSOR_HPP

#  include "server_defs.hpp"
#  include "subsystem.hpp"
#  include "logger.hpp"
#  include "noncopyable.hpp"

#  include <json.h>
#  include <string>

class command_processor_t : public subsystem_t
{
    ADD_CLASS_PREFIX_TO_LOG(command_processor_t)

    void start() override;
    void stop() override;

public:
    command_processor_t();

    Json::Value process_request(session_t *session, const Json::Value &request);

private:
    commands_map_t m_commands_map;
};

#endif // COMMAND_PROCESSOR_HPP
