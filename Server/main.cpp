#include <iostream>
#include <string>

#include <Networking/server/tcp_server.hpp>


using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    Networking::TCPServer server {Networking::IPV::V4, 1337};

    server.OnJoin = [](Networking::TCPConnection::pointer server){
        std::cout << "User has joined the server: " << server->GetUsername() << std::endl;

    };


    server.OnLeave = [](Networking::TCPConnection::pointer server){
        std::cout << "User has left the server: " << server->GetUsername() << std::endl;
    };

    server.OnClientMessage = [&server](const std::string& message){
        server.Broadcast(message);
    };

    server.Run();
    
    return 0;
}