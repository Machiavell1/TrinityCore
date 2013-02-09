/**
 * @file \src\server\irc\BaseSocketLayer.h
 *
 * @brief Declares the base socket layer class.
 */

#pragma once

#include "Common.h"

/**
 * @class BaseSocketLayer
 *
 * @brief Base socket layer.
 *
 * @author Machiavelli
 * @date 9-2-2013
 */

class BaseSocketLayer
{
    public:

        /**
         * @fn virtual bool BaseSocketLayer::Connect(char const* hostname, uint16 port) = 0;
         *
         * @brief Connects to the specified server.
         *
         * @author Machiavelli
         * @date 9-2-2013
         *
         * @param hostname The hostname to connect to.
         * @param port     The port to connect to.
         *
         * @return true if it succeeds, false if it fails.
         */

        virtual bool Connect(char const* hostname, uint16 port) = 0;

        /**
         * @fn virtual void BaseSocketLayer::Disconnect() = 0;
         *
         * @brief Disconnects the socket from the server
         *
         * @author Machiavelli
         * @date 9-2-2013
         */

        virtual void Disconnect() = 0;

        /**
         * @fn virtual bool BaseSocketLayer::Send(const char* data) = 0;
         *
         * @brief Sends data to the server
         *
         * @author Machiavelli
         * @date 9-2-2013
         *
         * @param data The data to be sent.
         *
         * @return true if it succeeds, false if it fails.
         */

        virtual bool Send(const char* data) = 0;

        /**
         * @fn virtual int BaseSocketLayer::Recv(char* buf) = 0;
         *
         * @brief Receives data from the server.
         *
         * @author Machiavelli
         * @date 9-2-2013
         *
         * @param [in,out] buf Buffer of data to be written to.
         *
         * @return Amount of bytes read or -1 if error.
         */

        virtual int Recv(char* buf) = 0;
};