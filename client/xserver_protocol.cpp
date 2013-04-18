#include "xserver_protocol.hpp"

#  include "reactions.hpp"

xserver_protocol_t::xserver_protocol_t()
{
}

protocol_state xserver_protocol_t::create_reaction(char* buffer, int buffer_size)
{
    char *end = nullptr;
    for(int i = 0; i<buffer_size; ++i)
    {
        if(buffer[i]=='\0')
        {
            end = &buffer[i] + 1;
            break;
        }
    }

    if(end)
    {
        size_t vector_size = buff_.size();
        buff_.resize(vector_size + (end-buffer));
        std::copy(buffer, end, buff_.begin()+vector_size);

        Json::Value value;
        Json::Reader reader;
        reader.parse(buff_.data(), buff_.data()+buff_.size()-1, value, false);

        xserver_reaction_iface_t::create(value);

        return  protocol_ok;
    }
    else
    {
        size_t vector_size = buff_.size();
        buff_.resize(vector_size + buffer_size);
        std::copy(buffer, buffer+buffer_size, buff_.begin()+vector_size);

        return protocol_need_more_bytes;
    }
}

protocol_type xserver_protocol_t::static_id()
{
    return XSERVER_PROTOCOL;
}

protocol_type xserver_protocol_t::id() const
{
    return XSERVER_PROTOCOL;
}
