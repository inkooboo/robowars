#include "command_processor.hpp"

command_processor_t::command_processor_t()
{
  // fill command handlers map
}

Json::Value command_processor_t::process_command(session_ptr &session, const Json::Value &command)
{
    Json::Value ret;

//    const Json::Value &id = request["id"];
//    const std::string &command = request["command"].asString();

//    response["id"] = id;
//    switch (m_state)
//    {
//    case st_connected:
//    {
//        // accept any user =)
//        m_user_info = std::make_shared<user_info_t>();
//        m_user_info->user_name = request["user"].asString();
//        m_user_info->password = request["password"].asString();
//        response["result"] = "ok";
//        m_state = st_authenticated;
//        log<debug>() << this << " authetificated with name " << m_user_info->user_name;
//        processed = true;
//    }
//    break;
//    case st_authenticated:
//    {

//    }
//    break;
//    case st_in_game:
//    {

//    }
//    break;
//    default:
//    break;
//    }



    return ret;
}



