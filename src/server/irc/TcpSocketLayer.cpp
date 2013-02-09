#include "TcpSocketLayer.h"

bool TcpSocketLayer::Connect(char const* hostname, uint16 port)
{
    _endPoint = ACE_INET_Addr(port, hostname, AF_INET);
    int ret = _connector.connect(_server, _endPoint);
    return ret != -1;
}

void TcpSocketLayer::Disconnect()
{
    _server.close();
}

bool TcpSocketLayer::Send(const char* data)
{
    std::string full = std::string(data) + "\n";
    return _server.send_n(full.c_str(), full.size()) != -1;
}

int TcpSocketLayer::Recv(char* buf)
{
    //ACE_Time_Value time(5);
    return _server.recv(buf, 2047) ;//, &time);
}