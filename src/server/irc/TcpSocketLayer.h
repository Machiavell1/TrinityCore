#pragma once

#include "BaseSocketLayer.h"

//#include <ace/SOCK_Stream.h>
#include <ace/SOCK_Connector.h>

class TcpSocketLayer : public BaseSocketLayer
{
    public:
        bool Connect(char const* hostname, uint16 port);
        void Disconnect();
        bool Send(const char* data);
        int Recv(char* buf);

    private:
        ACE_SOCK_Stream _server;
        ACE_SOCK_Connector _connector;
        ACE_INET_Addr _endPoint;
};