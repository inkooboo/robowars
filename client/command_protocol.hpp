#ifndef COMMAND_PROTOCOL_H
#define COMMAND_PROTOCOL_H

#  include "base_protocol.hpp"

#  include "json.h"

class command_protocol_t : public protocol_iface_t
{
public:
    command_protocol_t();

    static protocol_type static_id();

    protocol_state create_reaction(char* buffer, int buffer_size) override;
    std::vector<char> serialize_command(const Json::Value& command);

    protocol_type id() const override;

private:
    std::vector<char> buff_;
};

#endif // COMMAND_PROTOCOL_H
