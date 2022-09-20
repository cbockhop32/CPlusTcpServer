#include "Networking/tcp_server.hpp"
#include <iostream>

namespace Networking {

    using boost::asio::ip::tcp;

    TCPServer::TCPServer(IPV ipv, int port) : _ipVersion(ipv), _port(port),
        _acceptor(_ioContext, tcp::endpoint(_ipVersion == IPV::V4 ? tcp::v4() : tcp::v6(), _port))
    {
        
         
    }

    int TCPServer::Run() {

        try {
            startAccept();
        
            _ioContext.run();

        } catch(std::exception& e) {
            std::cerr << e.what() << std::endl;
            return -1;

        }

        return 0;
    }


    void TCPServer::startAccept()
    {
        // Create a connection
        auto connection = TCPConnection::Create(_ioContext);

        _connections.push_back(connection);


        // Asynchronously accept the connection
        _acceptor.async_accept(connection->Socket(), [connection, this](const boost::system::error_code& error) {
            if(!error) {
                connection->Start();
            }

            startAccept();

    });

      
    }





}

 