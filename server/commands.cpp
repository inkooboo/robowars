#include "commands.hpp"

#include "master.hpp"
#include "session.hpp"
#include "user_info.hpp"
#include "match_manager.hpp"

struct auth_command_t : public packet_iface_t
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

struct find_match_command_t : public packet_iface_t
{
    Json::Value process(session_ptr &session, const Json::Value &request) override
    {
        Json::Value result;

        unused_params(request);

        if (session->state() != session_t::st_authenticated)
        {
            result["result"] = "fail";
            result["error"] = "wrong session state";
        }
        else
        {
            master_t::subsystem<match_manager_t>().add_match_ready_session(session);

            session->state() = session_t::st_ready_for_game;

            log<debug>() << session->user_info()->user_name << " is ready for game now";

            result["result"] = "ok";
        }

        return result;
    }
};


struct disable_find_match_command_t : public packet_iface_t
{
    Json::Value process(session_ptr &session, const Json::Value &request) override
    {
        Json::Value result;

        unused_params(request);

        if (session->state() != session_t::st_authenticated)
        {
            result["result"] = "fail";
            result["error"] = "wrong session state";
        }
        else
        {
            master_t::subsystem<match_manager_t>().remove_match_ready_session(session);

            session->state() = session_t::st_authenticated;

            log<debug>() << session->user_info()->user_name << " is NOT ready for game now";

            result["result"] = "ok";
        }

        return result;
    }
};

struct ready_for_game_command_t : public packet_iface_t
{
    Json::Value process(session_ptr &session, const Json::Value &request) override
    {
        Json::Value result;

        unused_params(request);

        if (session->state() != session_t::st_ready_for_game)
        {
            result["result"] = "fail";
            result["error"] = "wrong session state";
        }
        else
        {
            match_ptr match = session->match().lock();

            if (!match)
            {
                result["status"] = "pending";
            }
            else
            {
                result["status"] = "ready";
                Json::Value &players = result["players"];
                players = Json::Value(Json::arrayValue);
                session_set_t &sessions = match->sessions();
                for (auto &s : sessions)
                {
                    players.append(s->user_info()->user_name);
                }

                session->state() = session_t::st_in_game;
            }

            result["result"] = "ok";
        }

        return result;
    }
};






commands_map_t get_commands_map()
{
    commands_map_t ret
    (
        {
              {"auth", std::make_shared<auth_command_t>()}
            , {"find_match", std::make_shared<find_match_command_t>()}
            , {"disable_find_match", std::make_shared<disable_find_match_command_t>()}
            , {"ready_for_game", std::make_shared<ready_for_game_command_t>()}

        }
        , COMMANDS_MAP_BUCKETS_COUNT
    );


    return ret;
}

