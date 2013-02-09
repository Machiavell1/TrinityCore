#include "RfcHandlers.h"
#include "IRCClient.h"
#include "IrcMessage.h"

void RfcHandlers::Handle001(IrcMessage& args)
{
    _client->Join("#defaultChan", "defaultPass");
}

void RfcHandlers::HandlePing(IrcMessage& args)
{
    args.Full[1] = 'O';
    _client->Send(args.Full.c_str());
}