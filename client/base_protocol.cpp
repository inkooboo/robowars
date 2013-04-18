#include "base_protocol.hpp"

#  include "command_protocol.hpp"
#  include "xserver_protocol.hpp"

static protocol_iface_t* protocol_iface_t::create(char type)
{
    protocol_iface_t* ret;
    switch(type)
    {
    case command_protocol_t::static_id():
    {
        ret = new command_protocol_t();
        break;
    }
    case xserver_protocol_t::static_id():
    {
        ret = new xserver_protocol_t();
    }
    default:
        log<critical>()<<"protocol determinate error. Unknown protocol.";
    }
}
