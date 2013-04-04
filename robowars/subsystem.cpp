#include "subsystem.hpp"

#include "master.hpp"

master_t & subsystem_t::master()
{
    return *m_master;
}
