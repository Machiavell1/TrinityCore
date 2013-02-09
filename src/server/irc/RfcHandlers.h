#pragma once

class RfcHandlers;
class IRCClient;
struct IrcMessage;

struct RfcCommand
{
    const char* Id;
    void (RfcHandlers::*Handler)(IrcMessage& args);
};

class RfcHandlers
{
    friend class IRCClient;
    public:
        void Handle001(IrcMessage& args);
        void HandlePing(IrcMessage& args);

    protected:
        RfcHandlers(IRCClient* client) : _client(client) {}

    private:
        IRCClient* _client;
};


const RfcCommand RfcCommands[] =
{
    {"001", &RfcHandlers::Handle001},
    {"PING", &RfcHandlers::HandlePing},
    {0,0}
};
