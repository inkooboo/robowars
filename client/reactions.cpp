#include "reactions.hpp"

class reaction_end_game : public command_reaction_iface_t
{
public:
    static void response(const packet_t& value)
    {

    }
};

void command_reaction_iface_t::create(const Json::Value& value)
{
    assert(value.isMember("command") && "Unknown command!!!");
    auto creator = this->get_creator(value["command"].asString());
    creator.create_reaction(value);
}

detail::command_reaction_creator_iface_t& command_reaction_iface_t::get_creator(const std::string& command_name)
{
    using namespace detail;
    typedef std::unordered_map<std::string, std::shared_ptr<command_reaction_creator_iface_t> > creators_map_t;
    static creators_map_t creators_map
            (
                {
                    {std::string("end game"), std::make_shared<reaction_creator_t<reaction_end_game> >()}
                }
                , COMMANDS_MAP_BUCKETS_COUNT
            );

    return *(creators_map[command_name]);
}

