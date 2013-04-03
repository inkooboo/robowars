#include "session.hpp"
#include "logger.hpp"
#include "server_defs.hpp"

# include <boost/asio.hpp>
# include <boost/bind.hpp>


session_t::session_t(boost::asio::io_service& io_service)
    : m_socket(io_service)
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
    unused_params(bytes_transferred);

    if (!error)
    {
//        Event evt = Event::parse(data_, bytes_transferred);

//        logger::log(DEBUG) << "[Session] Event got:\n" << evt.serialize();

//        if (!game)
//        {
//            game = master_t::subsystem<GameManager>().join_game(this, evt);
//            if (!game)
//            {
//                Event notify = Event::create(EV_NOTIFY);
//                notify["message"] = "Max game limit exceed";
//                send_event(notify);
//                delete this;
//                return;
//            }
//        }
//        else
//        {
//            game->on_event(evt);
//        }

        start_read();
    }
    else
    {
//		if (game)
//        {
//	        _master->subsystem<GameManager>().leave_game(game->id, this);
//		}
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
//		if (game)
//        {
//	        _master->subsystem<GameManager>().leave_game(game->id, this);
//		}
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
