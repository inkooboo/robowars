#ifndef XSERVER_HPP
#define XSERVER_HPP

#  include "subsystem.hpp"
#  include "logger.hpp"

#include "mainwindow.h"

class xserver_t :  public subsystem_t
{

    ADD_CLASS_PREFIX_TO_LOG(xserver)

    virtual void start() override;
    virtual void stop() override;

public:
    xserver_t();

private:
    MainWindow window_;
};

#endif // XSERVER_HPP
