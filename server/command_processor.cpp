#include "command_processor.hpp"

#include "commands.hpp"

command_processor_t::command_processor_t()
    : m_commands_map(COMMANDS_MAP_BUCKETS_COUNT)
{
}

void command_processor_t::start()
{
    log<debug>() << "starting";

    m_commands_map = get_commands_map();

    log<debug>() << m_commands_map.size() << " commands in commands map";
}

void command_processor_t::stop()
{
    log<debug>() << "stopping";
}

Json::Value command_processor_t::process_request(session_ptr &session, const Json::Value &request)
{
    Json::Value response;

    const Json::Value &id = request["id"];
    const std::string &command = request["command"].asString();

    auto command_found = m_commands_map.find(command);
    if (m_commands_map.end() != command_found)
    {
        command_iface_ptr &handler = command_found->second;
        Json::Value result = handler->process(session, request);
        response.swap(result);
    }
    else
    {
        response["result"] = "fail";
        response["error"] = "command not found in command map";
    }

    response["id"] = id;

    return response;
}



