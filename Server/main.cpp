#include <iostream>
#include <string>

#include <Networking/tcp_server.hpp>


using boost::asio::ip::tcp;

int main(int argc, char* argv[])
{
    Networking::TCPServer server {Networking::IPV::V4, 1337};

    server.Run();
    
    return 0;
}