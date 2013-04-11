#include "packetyzer.hpp"
#include <list>
#include <string>
#include <iostream>

const static char message1[] = "{this is a good small packet}";
const static char message2[] = "{first packet}\0{second packet}";
const static char message3[] = "{partial packet complete part1}\0{partial packet begin"; // use length - 1
const static char message4[] = " partial packet end}\0{partial packet complete part2}";

static std::list<std::string> waiting_results = {
      "{this is a good small packet}"
    , "{first packet}"
    , "{second packet}"
    , "{partial packet complete part1}"
    , "{partial packet begin partial packet end}"
    , "{partial packet complete part2}"
};

static bool result = true;
static std::list<std::string>::iterator cur = waiting_results.begin();

void check_packet(const char *begin, const char *end)
{
    std::string packet(begin, end);

    std::cout << "on_packet: " << packet;
    if (cur == waiting_results.end())
    {
        result = false;
        return;
    }

    std::cout << " VS " << *cur << std::endl;
    if (*cur != packet)
    {
        result = false;
        return;
    }
    ++cur;
}

bool unit_test_packetyzer()
{
    packetyzer_t packetizer;

    packetizer.parse_buffer(check_packet, message1, sizeof(message1));
    packetizer.parse_buffer(check_packet, message2, sizeof(message2));
    packetizer.parse_buffer(check_packet, message3, sizeof(message3) - 1);
    packetizer.parse_buffer(check_packet, message4, sizeof(message4));

    return result && (cur == waiting_results.end());
}
