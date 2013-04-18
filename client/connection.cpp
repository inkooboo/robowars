#include "connection.hpp"

#include "command_protocol.hpp"

connection_t::connection_t()
    : buff_size_(0)
    , buff_cursor_(buff_)
{
}

void connection_t::connect(const std::string& url, size_t port)
{
    socket_.connectToHost(url, port);
    connect(socket_, SIGNAL(readyRead()), this, SLOT(handle_read()) );
    connect(socket_, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(handle_error(QAbstractSocket::SocketError)) );
}

void connection_t::disconnect()
{
    socket_.disconnectFromHost();
}

void connection_t::send(const std::vector<char> &data)
{
    socket_.write(data.data(), data.size());
}

void connection_t::handle_read()
{
    size_t read_size = socket_.read(buff_, MAX_BUFF_LENGTH);
    char* cursor = &buff[0];

    if(read_size < 1) return;

    if(!current_protocol_)
    {
        current_protocol_.reset(protocol_iface_t::create(buff_[0]));
        ++cursor;
        --read_size;
    }

    protocol_state st = current_protocol_->create_reaction(cursor, read_size);
    switch (st)
    {
        case protocol_ok:
        {
            current_protocol_.reset();
            break;
        }
        case protocol_error:
        {
            log<critical>()<<"protocol parse error: "<<current_protocol_->error();
            break;
        }
    }

}

void connection_t::handle_error(const QAbstractSocket::SocketError &)
{
    log<critical>()<<"socket error: "<<socket_.errorString();
}
