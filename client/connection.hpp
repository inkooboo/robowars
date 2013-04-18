#ifndef CONNECTION_HPP
#define CONNECTION_HPP

#  include <QTcpSocket>

#  include <string>
#  include <memory>

#  include "logger.hpp"
#  include "base_protocol.hpp"

class connection_t : public QObject
{
    ADD_CLASS_PREFIX_TO_LOG(connection)

public:
    connection_t();

    void connect(const std::string& url, size_t port);
    void disconnect();

    void send(const std::vector<char> &data);

private slots:
    void handle_read();
    void handle_error(const QAbstractSocket::SocketError &);

private:
    const static int MAX_BUFF_LENGTH = 8192 * 2;
    char buff_[MAX_BUFF_LENGTH];

    QTcpSocket socket_;

    int buff_size_;
    char* buff_cursor_;
    std::unique_ptr<protocol_iface_t> current_protocol_;
};

#endif // CONNECTION_HPP
