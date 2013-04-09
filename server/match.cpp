#include "match.hpp"
#include "session.hpp"
#include "scheduler.hpp"
#include "master.hpp"
#include "field.hpp"
#include "match_manager.hpp"

const static size_t TIME_PER_SIMULATION_TICK_MS = 25;
const static size_t TIME_PER_XSERVER_MESSAGE_MS = 100;

match_t::match_t(const session_set_t &sessions, boost::asio::io_service &io_svc)
    : m_state(st_created)
    , m_io_svc(io_svc)
    , m_sessions(sessions)
    , m_field(std::make_shared<field_t>())
{
    log<debug>() << "created match " << this;
}

match_t::~match_t()
{
    log<debug>() << "destroyed match " << this;
}

void match_t::on_time_chunk()
{
    if (st_ending == m_state)
    {
        log<debug>() << "match stopped " << this;
        return;
    }

    typedef std::chrono::duration<float,std::milli> milliseconds_type;
    std::chrono::high_resolution_clock::time_point now = std::chrono::high_resolution_clock::now();
    milliseconds_type ms = std::chrono::duration_cast<milliseconds_type> (now - m_last_time);
    m_last_time = now;
    float dt_ms = ms.count();

    //field step
    m_field->on_time_chunk(dt_ms);

    master_t::subsystem<scheduler_t>().schedule(std::bind(&match_t::on_time_chunk, shared_from_this()), TIME_PER_SIMULATION_TICK_MS);

    // xserver messages
    m_xserver_message_time_ms += dt_ms;
    if (m_xserver_message_time_ms > TIME_PER_XSERVER_MESSAGE_MS)
    {
        m_xserver_message_time_ms -= TIME_PER_XSERVER_MESSAGE_MS;

        std::string xserver_message = m_field->xserver_field_dump();

        bool all_session_invalid = true;
        for (auto &s : m_sessions)
        {
            if (s->valid())
            {
                all_session_invalid = false;
            }

            s->send_data(&xserver_message[0], xserver_message.length());
        }

        if (all_session_invalid)
        {
            // all disconnected
            // shutdown match
            stop();
        }
    }
}

session_set_t & match_t::sessions()
{
    return m_sessions;
}

void match_t::start()
{
    log<debug>() << "starting match " << this;

    m_state = st_started;

    bool all_in_game = true;
    for (auto & s : m_sessions)
    {
        if (s->state() != session_t::st_in_game)
        {
            all_in_game = false;
            break;
        }
    }

    if (!all_in_game)
    {
        log<debug>() << "wait for all clients to be in 'in_game' state for match " << this;
        master_t::subsystem<scheduler_t>().schedule(std::bind(&match_t::start, shared_from_this()), 1000);
        return;
    }

    log<debug>() << "started match " << this;

    m_last_time = std::chrono::high_resolution_clock::now();
    m_xserver_message_time_ms = 0.f;
    on_time_chunk();
}

void match_t::stop()
{
    log<debug>() << "stopping match " << this;
    m_state = st_ending;
    match_manager_t &manger = master_t::subsystem<match_manager_t>();
    master_t::subsystem<scheduler_t>().schedule(std::bind(&match_manager_t::remove_match, &manger, shared_from_this()), 1000);
}



