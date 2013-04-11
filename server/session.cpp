#include "session.hpp"

#include "logger.hpp"
#include "user_info.hpp"
#include "master.hpp"
#include "command_processor.hpp"

#include <json.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

session_t::session_t(boost::asio::io_service& io_service)
    : m_socket(io_service)
    , m_user_info(std::make_shared<user_info_t>())
    , m_state(st_connected)
    , m_valid(true)
{
    log<debug>() << this << " session created";
}

session_t::~session_t()
{
    log<debug>() << this << " session destructed";
}

boost::asio::ip::tcp::socket & session_t::socket()
{
    return m_socket;
}

session_t::state_t & session_t::state()
{
    return m_state;
}

user_info_ptr & session_t::user_info()
{
    return m_user_info;
}

std::atomic<bool> & session_t::valid()
{
    return m_valid;
}

match_weak_ptr & session_t::match()
{
    return m_match;
}

void session_t::start_read()
{
    if (!m_valid)
    {
        return;
    }

    m_socket.async_read_some(boost::asio::buffer(m_data, MAX_DATA_LENGTH),
                             boost::bind(&session_t::handle_read, shared_from_this(),
                             boost::asio::placeholders::error,
                             boost::asio::placeholders::bytes_transferred));
}

std::string stringize_json(const char *begin, const char *end)
{
    std::string ret(begin, end);

    for (auto &c : ret)
    {
        if (c == '\'')
        {
            c = '\'';
        }
    }

    return ret;
}

void session_t::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!m_valid)
    {
        return;
    }

    session_ptr this_ptr = shared_from_this();

    if (error)
    {
        m_valid = false;
        return;
    }

    auto on_packet = [&](const char *begin, const char *end)
    {
#ifdef DEBUG_PROTO
        log<debug>() << this << " RECEIVED:\n" << std::string(begin, end);
#endif
        if (*begin != 'g')
        {
            Json::Value error;
            error["error"] = "protocol error";
            error["bad_packet"] = stringize_json(begin, end);
            send_message(error);
        }
        else
        {
            ++begin; // skip 'g'

            Json::Reader reader;
            Json::Value request;
            reader.parse(begin, end, request, false);

            const Json::Value &response = master_t::subsystem<command_processor_t>().process_request(this_ptr, request);

            response["id"] = request["id"];

            send_message(response);
        }
    };

    m_packetyzer.parse_buffer(on_packet, &m_data[0], bytes_transferred);

    start_read();
}

void session_t::handle_write(const boost::system::error_code& error)
{
    if (!m_valid)
    {
        return;
    }

    session_ptr this_ptr = shared_from_this();

    if (!error)
    {
    }
    else
    {
        m_valid = false;
    }
}

void session_t::send_message(const Json::Value &response)
{
#ifdef DEBUG_PROTO
    Json::StyledWriter writer;
#else
    Json::FastWriter writer;
#endif
    const std::string &serialized = writer.write(response);

#ifdef DEBUG_PROTO
        log<debug>() << this << " SEND:\n" << serialized;
#endif

    send_data(&serialized[0], serialized.length());
}

void session_t::send_data(const char *begin, size_t size)
{
    if (!m_valid)
    {
        return;
    }

    boost::asio::async_write(m_socket,
                             boost::asio::buffer(begin, size),
                             boost::bind(&session_t::handle_write, shared_from_this(),
                             boost::asio::placeholders::error));
}

