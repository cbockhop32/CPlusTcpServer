#pragma once

#include <boost/asio.hpp>
#include <memory>

namespace Networking {
    using boost::asio::ip::tcp;

    class TCPConnection : public std::enable_shared_from_this<TCPConnection> {

    public:
        using pointer = std::shared_ptr<TCPConnection>;
        static pointer Create(boost::asio::io_context& ioContext) {
            return pointer(new TCPConnection(ioContext));
        }
        // Getter for the socket
        tcp::socket& Socket(){
            return _socket;
        }

        void Start();

    private:
        explicit TCPConnection(boost::asio::io_context& ioContext);

    private:
        tcp::socket _socket;
        std::string _message {"Hello, client\n"};

    };
}