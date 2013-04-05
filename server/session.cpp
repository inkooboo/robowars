#include "session.hpp"
#include "logger.hpp"
#include "user_info.hpp"

#include <json.h>

#include <boost/asio.hpp>
#include <boost/bind.hpp>

session_t::session_t(boost::asio::io_service& io_service)
    : m_socket(io_service)
    , m_state(st_empty)
{
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
        Json::Reader reader;
        Json::Value parsed;
        reader.parse(&m_data[0], &m_data[bytes_transferred], parsed, false);

        const Json::Value &id = parsed["id"];
        const std::string &command = parsed["command"].asString();

        switch (m_state)
        {
        case st_empty:
        {
            m_user_info = std::make_shared<user_info_t>();

        }
        break;
        case st_connected:
        {

        }
        break;
        case st_authenticated:
        {

        }
        break;
        case st_in_game:
        {

        }
        break;
        default:
        break;
        }
    }
    else
    {
        delete this;
    }
}

void session_t::handle_write(const boost::system::error_code& error)
{
    if (!error)
    {
    }
    else
    {
        delete this;
    }
}

//void session_t::send_event(const Event &evt)
//{
//    std::string serialized = evt.serialize();
//    logger::log(DEBUG) << "[Session] Send event:\n" << serialized;
//    boost::asio::async_write(socket_,
//                             boost::asio::buffer(serialized.c_str(), serialized.length()),
//                             boost::bind(&Session::handle_write, this,
//                             boost::asio::placeholders::error));
//}
