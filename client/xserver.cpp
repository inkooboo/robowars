#include "xserver.hpp"

xserver_t::xserver_t()
{
}

void xserver_t::start()
{
    window_.showw();
}

void xserver_t::stop()
{
    window_.hide();
}
