#pragma once

#include "BaseSocketLayer.h"

#include <ace/SOCK_Connector.h>

/**
 * @class TcpSocketLayer
 *
 * @brief TCP socket layer. Implements methods from @BaseSocketLayer
 *
 * @author Machiavelli
 * @date 9-2-2013
 */

class TcpSocketLayer : public BaseSocketLayer
{
    public:
        bool Connect(char const* hostname, uint16 port);
        void Disconnect();
        bool Send(const char* data);
        int Recv(char* buf);

    private:
        ACE_SOCK_Stream _server;	            ///< The socket stream to the server
        ACE_SOCK_Connector _connector;      ///< The connector interface, only used for just that
        ACE_INET_Addr _endPoint;	           ///< The TCP endpoint to connect to 
};