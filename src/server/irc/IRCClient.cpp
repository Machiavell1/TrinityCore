#include "IRCClient.h"
#include "BaseSocketLayer.h"
#include "SslSocketLayer.h"
#include "TcpSocketLayer.h"
#include "IrcMessage.h"
#include "RfcHandlers.h"
#include "SystemConfig.h"

#define MAX_FMT_SIZE 1024

IRCClient::IRCClient() : _handlers(this)
{
    const bool use_ssl = false;
    if (use_ssl)
    ;//    _socket = new SslSocketLayer;
    else
        _socket = new TcpSocketLayer;

    if (!_socket->Connect("defaultServ", 6667))
    {
        printf("Something went wrong connecting, bro");
        return;
    }

    Send("PASS abc"); //, "abc");
    Send("NICK TrinityCore");
    Send("USER TrinityCore TrinityCore TrinityCore :TrinityCore <%s>", _FULLVERSION);
}

IRCClient::~IRCClient()
{
    delete _socket;
}

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

int IRCClient::Recv(char* buf)
{
    return _socket->Recv(buf);
}

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

void IRCClient::Join(const char* channel, const char* key)
{
    if (key)
        Send("JOIN %s %s", channel, key);
    else
        Send("JOIN %s", channel);
}

void IRCClient::Part(const char* channel, const char* message)
{
    if (message)
        Send("PART %s :\"%s\"", channel, message);
    else
        Send("PART %s", channel);
}

void IRCClient::Quit(const char* quitMsg)
{
    if (quitMsg)
        Send("QUIT :\"%s\"", quitMsg);
    else
        Send("QUIT");
    _socket->Disconnect();
}

void IRCClient::Nick(const char* nick)
{
    Send("NICK %s", nick);
}