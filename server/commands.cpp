#include "commands.hpp"

#include "session.hpp"
#include "user_info.hpp"

struct auth_command_t : public command_iface_t
{
    Json::Value process(session_ptr &session, const Json::Value &request) override
    {
        Json::Value result;

        if (session->state() != session_t::st_connected)
        {
            result["result"] = "fail";
            result["error"] = "wrong session state";
        }
        else
        {
            //auth
            // accept any user =)

            user_info_ptr user_info = std::make_shared<user_info_t>();
            user_info->user_name = request["user"].asString();
            user_info->password = request["password"].asString();

            session->state() = session_t::st_authenticated;
            session->user_info() = user_info;

            log<debug>() << session.get() << " sucessfully authetificated with name " << user_info->user_name;

            result["result"] = "ok";
        }

        return result;
    }
};

struct ready_for_game_command_t : public command_iface_t
{
    Json::Value process(session_ptr &session, const Json::Value &request) override
    {
        Json::Value result;

        (void)session;
        (void)request;

        return result;
    }
};










commands_map_t get_commands_map()
{
    commands_map_t ret
    (
        {
              {"auth", std::make_shared<auth_command_t>()}
            , {"ready_for_game", std::make_shared<ready_for_game_command_t>()}

        }
        , COMMANDS_MAP_BUCKETS_COUNT
    );


    return ret;
}

