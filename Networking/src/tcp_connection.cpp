#include "Networking/tcp_connection.hpp"
#include <iostream>

namespace Networking {

    TCPConnection::TCPConnection(boost::asio::io_context& ioContext) : _socket(ioContext) {

    }

    void TCPConnection::Start() {
        auto strongThis = shared_from_this();
        boost::asio::async_write(_socket, boost::asio::buffer(_message),
                            [strongThis] (const boost::system::error_code& error, size_t bytesTransferred) {
            if(error) {
                std::cout << "Failed to send message \n";
            } else {
                std::cout << "Sent" << bytesTransferred << " bytes of data!\n";
            }
                            });

        boost::asio::streambuf buffer;
        _socket.async_receive(buffer.prepare(512), 
        [this](const boost::system::error_code error, size_t  bytesTransferred){
            if(error == boost::asio::error::eof)
            {
                std::cout << "Client disconnected properly\n";
            } else if (error) {
                throw boost::system::system_error(error);
            }
        });
    }


}