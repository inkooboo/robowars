#include "packetyzer.hpp"
#include <algorithm>

void packetyzer_t::parse_buffer(on_packet_cb_t cb, const char *begin, size_t length)
{
    internal_parse_buffer(cb, begin, begin + length, !m_remaning.empty());
}

void packetyzer_t::internal_parse_buffer(on_packet_cb_t cb, const char *begin, const char *end, bool have_remaning)
{
    if (!have_remaning)
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
            m_remaning.assign(packet_begin, end);
        }
    }
    else
    {
        m_remaning.reserve(m_remaning.size() + (end - begin));
        std::copy(begin, end, &m_remaning[m_remaning.size()]);

        internal_parse_buffer(cb, &m_remaning[0], &m_remaning[m_remaning.size() + (end - begin)], false);
    }
}
