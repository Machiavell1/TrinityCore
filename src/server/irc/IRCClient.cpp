/**
 * @file \src\server\irc\IRCClient.cpp
 *
 * @brief Implements the irc client class.
 */

#include "IRCClient.h"
#include "BaseSocketLayer.h"
#include "SslSocketLayer.h"
#include "TcpSocketLayer.h"
#include "IrcMessage.h"
#include "RfcHandlers.h"
#include "SystemConfig.h"

/**
 * @def MAX_FMT_SIZE
 *
 * @brief A macro that defines maximum format size.
 *
 * @author Machiavelli
 * @date 9-2-2013
 */

#define MAX_FMT_SIZE 1024

IRCClient::IRCClient() : _handlers(this)
{
    const bool use_ssl = false;
    if (use_ssl)
    ;//    _socket = new SslSocketLayer;
    else
        _socket = new TcpSocketLayer;

    if (!_socket->Connect("irc.test.org", 6666))
    {
        printf("Something went wrong connecting, bro");
        return;
    }

    Send("PASS abc"); //, "abc");
    Send("NICK TrinityCore");
    Send("USER TrinityCore TrinityCore TrinityCore :TrinityCore <%s>", _FULLVERSION);
}

/**
 * @fn IRCClient::~IRCClient()
 *
 * @brief Destructor.
 *
 * @author Machiavelli
 * @date 9-2-2013
 */

IRCClient::~IRCClient()
{
    delete _socket;
}

/**
 * @fn void IRCClient::Send(const char* data, ...)
 *
 * @brief Send data to the server and format string if needed.
 *
 * @author Machiavelli
 * @date 9-2-2013
 *
 * @param data The data to send.
 */

void IRCClient::Send(const char* data, ...)
{
    char buf[MAX_FMT_SIZE];
    va_list args;
    va_start(args, data);
    vsnprintf(buf, MAX_FMT_SIZE-1, data, args);
    va_end(args);

    printf(">>");
    printf(buf);
    printf("\n");
    _socket->Send(buf);
}

/**
* @fn int IRCClient::Recv(char* buf);
*
* @brief Calls underlying Recv from socket.
*
* @author Machiavelli
* @date 9-2-2013
*
* @param [in,out] buf The buffer to write data to.
*
* @return Amount of bytes received or -1 for error.
*/

int IRCClient::Recv(char* buf)
{
    return _socket->Recv(buf);
}

/**
* @fn void IRCClient::HandleMessage(const char* data);
*
* @brief Handles incoming messages from the server.
*
* @author Machiavelli
* @date 9-2-2013
*
* @param data The data received.
*/

void IRCClient::HandleMessage(const char* data)
{
    if (!strncmp(data, ":ERROR", 6))
    {
        Quit("Error bro");
        return;
    }

    if (strstr(data, "PING"))
    {
        ((char*)data)[1] = 'O';
        Send(data);
    }

    IrcMessage msg(data);
    for (uint32 i = 0; ;++i)
    {
        if (!RfcCommands[i].Id || !RfcCommands[i].Handler)
            return;

        if (!strcmp(RfcCommands[i].Id, msg.Command.c_str()))
        {
            (_handlers.*RfcCommands[i].Handler)(msg);
            return;
        }
    }
}

/**
* @fn void IRCClient::Join(const char* channel, const char* key = NULL);
*
* @brief Joins specified channel on the IRC server.
*
* @author Machiavelli
* @date 9-2-2013
*
* @param channel The channel.
* @param key     (optional) the channel key.
*/

void IRCClient::Join(const char* channel, const char* key)
{
    if (key)
        Send("JOIN %s %s", channel, key);
    else
        Send("JOIN %s", channel);
}

/**
* @fn void IRCClient::Part(const char* channel, const char* message = NULL);
*
* @brief Parts a channel on the IRC server.
*
* @author Machiavelli
* @date 9-2-2013
*
* @param channel The channel to part.
* @param message (optional) Message to send to channel on leave.
*/

void IRCClient::Part(const char* channel, const char* message)
{
    if (message)
        Send("PART %s :\"%s\"", channel, message);
    else
        Send("PART %s", channel);
}

/**
* @fn void IRCClient::Quit(const char* quitMsg = "IRCClient::_defaultQuitMsg");
*
* @brief Quits from the IRC server.
*
* @author Machiavelli
* @date 9-2-2013
*
* @param quitMsg (optional) Quit message to send to server.
*/

void IRCClient::Quit(const char* quitMsg)
{
    if (quitMsg)
        Send("QUIT :\"%s\"", quitMsg);
    else
        Send("QUIT");
    _socket->Disconnect();
}

/**
* @fn void IRCClient::Nick(const char* nick);
*
* @brief Changes nickname,
*
* @author Machiavelli
* @date 9-2-2013
*
* @param nick The new nickname.
*/

void IRCClient::Nick(const char* nick)
{
    Send("NICK %s", nick);
}