#ifndef REACTION_HPP
#define REACTION_HPP

#  include "base_protocol.hpp"
#  include "command_protocol.hpp"
#  include "xserver_protocol.hpp"

#  include "json.h"

#  include <unordered_map>

const static size_t COMMANDS_MAP_BUCKETS_COUNT = 1024;

class reaction_iface_t
{
public:
    virtual ~reaction_iface_t() { }
};

namespace detail
{
    template <typename packet>
    class reaction_creator_iface_t
    {
    public:
        virtual ~reaction_creator_iface_t() { }

        virtual void create_reaction(packet const&) = 0;
    };

    template <typename reaction>
    class reaction_creator_t : public reaction_creator_iface_t<typename reaction::packet_t>
    {
    public:
        void create_reaction(typename reaction::packet_t const& value) override
        {
            return reaction::response(value);
        }
    };

    typedef reaction_creator_iface_t<Json::Value> command_reaction_creator_iface_t;
    typedef reaction_creator_iface_t<Json::Value> xserver_reaction_creator_iface_t;
}//end namespace detail

class xserver_reaction_iface_t : public reaction_iface_t
{
public:
    typedef xserver_protocol_t protocol;
    typedef Json::Value packet_t;

    static void create(const packet_t& value);
};

class command_reaction_iface_t : public reaction_iface_t
{
public:
    typedef command_protocol_t protocol;
    typedef Json::Value packet_t;

    static void create(const packet_t& value);

private:
    detail::command_reaction_creator_iface_t& get_creator(const std::string& command_name);
};

#endif // REACTION_HPP
