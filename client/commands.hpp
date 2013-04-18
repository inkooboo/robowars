#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#  include <json.h>

#  include "command_protocol.hpp"

class packet_iface_t : private noncopyable_t
{
public:
    virtual ~packet_iface_t() {}

    virtual void execute() = 0;
};

class command_iface_t : public packet_iface_t
{
public:
    typedef command_protocol protocol;

protected:
    void wait_response();
    void send(const Json::Value& data);
};

class xserver_command_iface_t : public packet_iface_t
{
public:
    typedef xserver_protocol protocol;
};

namespace commands
{

    class auth : public command_iface_t
    {
    public:
        auth(const std::string& player, const std::string& password);

        void execute() override;

    private:
        std::string player_;
        std::string password_;
    };

    class find_match : public command_iface_t
    {
    public:
        find_match();

        void execute() override;
    };

}//end namespace commands

#endif // COMMANDS_HPP
