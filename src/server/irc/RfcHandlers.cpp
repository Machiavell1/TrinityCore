/**
 * @file src\server\irc\RfcHandlers.cpp
 *
 * @brief Implements the RFC command handlers.
 */

#include "RfcHandlers.h"
#include "IRCClient.h"
#include "IrcMessage.h"

/**
 * @fn void RfcHandlers::Handle001(IrcMessage& args)
 *
 * @brief Handles the 001/"Welcome to the server" message.
 *
 * @author Machiavelli
 * @date 9-2-2013
 *
 * @param args The message content.
 */

void RfcHandlers::Handle001(IrcMessage&/* args*/)
{
    _client->Join("#test", "test");
}
