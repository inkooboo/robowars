#ifndef XSERVER_PROTOCOL_HPP
#define XSERVER_PROTOCOL_HPP

#  include "base_protocol.hpp"

class xserver_protocol_t : public protocol_iface_t
{
public:
    xserver_protocol_t();

    static protocol_type static_id();

    protocol_state create_reaction(char* buffer, int buffer_size) override;

    protocol_type id() const override;

private:
    std::vector<char> buff_;
};

#endif // XSERVER_PROTOCOL_HPP
