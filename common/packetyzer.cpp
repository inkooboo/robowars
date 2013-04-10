#include "packetyzer.hpp"
#include <algorithm>

void packetyzer_t::parse_buffer(on_packet_cb_t cb, const char *begin, size_t length)
{
    const char *end = begin + length;
    // optimistic scenario
    // some packets per one buffer and no remanings
    // no reallocations will occur
    if (m_remaning.empty())
    {
        const char *packet_begin = begin;
        for (const char *cur = begin; cur != end; ++cur)
        {
            if (*cur == PAKET_DELIMITER)
            {
                cb(packet_begin, cur);
                packet_begin = cur + 1;
            }
        }

        if (packet_begin != end)
        {
            // save some remanings
            m_remaning.assign(packet_begin, end);
        }
    }
    else
    {
        m_remaning.reserve(m_remaning.size() + length);
        std::copy(begin, end, &m_remaning[m_remaning.size()]);

        std::vector<char> buff;
        buff.swap(m_remaning);
        parse_buffer(cb, &buff[0], buff.size());
    }
}

