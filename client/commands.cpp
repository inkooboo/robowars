#include "commands.hpp"

#  include "master.hpp"
#  include "network.hpp"

namespace commands
{

    void command_iface_t::wait_response()
    {

    }

    void command_iface_t::send(const Json::Value &data)
    {
        std::vector<char> buff;
        command_protocol_t protocol;
        buff.swap(protocol.serialize_command(data));
        master_t::subsystem<network>().send(buff);
    }



    auth::auth(const std::string& player, const std::string& password)
        : player_(player)
        , password_(password)
    {
    }

    void auth::execute()
    {
        Json::Value data;
        data["id"] = 0;
        data["command"] = "auth";
        data["user"] = user_;
        data["password"] = password_;

        send(data);
        wait_response();
    }

    find_match::find_match()
    {
    }

    void find_match::execute()
    {
        Json::Value data;
        data["id"] = 1;
        data["command"] = "find_match";

        send(data);
        wair_response();
    }

}//end namespace commands
