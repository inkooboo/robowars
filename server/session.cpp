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
{
}

session_ptr session_t::create(boost::asio::io_service& io_service)
{
    session_ptr ret(new session_t(io_service));
    ret->m_this_ptr = ret;
    return ret;
}

void session_t::destroy()
{
    m_this_ptr.reset();
}


session_t::state_t & session_t::state()
{
    return m_state;
}

user_info_ptr & session_t::user_info()
{
    return m_user_info;
}

boost::asio::ip::tcp::socket& session_t::socket()
{
    return m_socket;
}

void session_t::start_read()
{
    m_socket.async_read_some(boost::asio::buffer(m_data, MAX_DATA_LENGTH),
                            boost::bind(&session_t::handle_read, this,
                            boost::asio::placeholders::error,
                            boost::asio::placeholders::bytes_transferred));
}

void session_t::handle_read(const boost::system::error_code& error, size_t bytes_transferred)
{
    if (!error)
    {
        //realize concatenating data if not all received

        Json::Reader reader;
        Json::Value request;
        reader.parse(&m_data[0], &m_data[bytes_transferred], request, false);

#ifdef DEBUG_PROTO
        log<debug>() << this << " RECEIVED:\n" << std::string(&m_data[0], bytes_transferred);
#endif
        session_ptr session_holder = m_this_ptr;
        const Json::Value &response = master_t::subsystem<command_processor_t>().process_request(session_holder, request);

        send_message(response);
     }
    else
    {
        destroy();
    }
}

void session_t::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
    }
    else
    {
        destroy();
    }
}

void session_t::send_message(const Json::Value &response)
{
#ifdef DEBUG_PROTO
    Json::StyledWriter writer;
#else
    Json::Writer writer;
#endif
    const std::string &serialized = writer.write(response);

#ifdef DEBUG_PROTO
        log<debug>() << this << " SEND:\n" << serialized;
#endif

    boost::asio::async_write(m_socket,
                             boost::asio::buffer(serialized.c_str(), serialized.length()),
                             boost::bind(&session_t::handle_write, this,
                             boost::asio::placeholders::error));
}
