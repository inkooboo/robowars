#ifndef PACKETYZER_HPP
#  define PACKETYZER_HPP

#  include "noncopyable.hpp"
#  include <vector>
#  include <functional>

typedef std::function<void(const char *begin, const char *end)> on_packet_cb_t;

class packetyzer_t : private noncopyable_t
{
public:
    static const char PAKET_DELIMITER = '\0';

    void parse_buffer(on_packet_cb_t cb, const char *begin, size_t length);

private:
    void internal_parse_buffer(on_packet_cb_t cb, const char *begin, const char *end, bool have_remaning);

    std::vector<char> m_remaning;
};

#endif // PACKETYZER_HPP
