#ifndef BASE_PROTOCOL_H
#define BASE_PROTOCOL_H

enum class protocol_type
{
    COMMAND_PROTOCOL,
    XSERVER_PROTOCOL
};

enum class protocol_state
{
    protocol_ok,
    protocol_error,
    protocol_need_more_bytes
};

class protocol_iface_t
{
public:
    static protocol_iface_t* create(char type);

    virtual protocol_state create_reaction(char* buffer, int buffer_size) = 0;

    virtual protocol_type id() const = 0;
};

#endif // BASE_PROTOCOL_H
