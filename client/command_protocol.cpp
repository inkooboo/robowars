#include "command_protocol.hpp"

#  include "reactions.hpp"

protocol_state command_protocol_t::create_reaction(char* buffer, int buffer_size)
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

        command_reaction_iface_t::create(value);

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

std::vector<char> command_protocol_t::serialize_command(const Json::Value& command)
{
    Json::Writer writer;
    const std::string& str = writer.write(command);

    std::vector<char> ret(str.size());

    std::copy(str.begin(), str.end(), ret.begin());
    ret.push_back('\0');

    return ret;
}

protocol_type command_protocol_t::static_id()
{
    return COMMAND_PROTOCOL;
}

protocol_type command_protocol_t::id() const
{
    return COMMAND_PROTOCOL;
}
