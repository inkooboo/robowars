#ifndef NETWORK_HPP
#define NETWORK_HPP

#  include "subsystem.hpp"
#  include "logger.hpp"
#  include "connection.hpp"
#  include "base_protocol.hpp"

#  include <QTcpSocket>


class network_t :  public subsystem_t
{
    ADD_CLASS_PREFIX_TO_LOG(network)

    virtual void start() override;
    virtual void stop() override;

public:
    network_t();

    void send(const std::vector<char>& data);

private:
    connection_t connection_;
};

#endif // NETWORK_HPP
