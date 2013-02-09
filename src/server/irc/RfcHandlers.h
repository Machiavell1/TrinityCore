/**
 * @file src\server\irc\RfcHandlers.h
 *
 * @brief Declares the rfc handlers class.
 */

#pragma once

class RfcHandlers;
class IRCClient;
struct IrcMessage;

/**
 * @struct RfcCommand
 *
 * @brief Rfc command.
 *
 * @author Machiavelli
 * @date 9-2-2013
 */

struct RfcCommand
{
    const char* Id;                                 ///< String identifier of the command. Numeric codes also treated as strings.
    void (RfcHandlers::*Handler)(IrcMessage& args);     ///< Function pointer to handler wirh arguments @args
};

class RfcHandlers
{
    friend class IRCClient;
    public:
        void Handle001(IrcMessage& /*args*/);

    protected:

        /**
         * @fn RfcHandlers::RfcHandlers(IRCClient* client)
         *
         * @brief Constructor.
         *
         * @author Machiavelli
         * @date 9-2-2013
         *
         * @param client The underlying IRC client.
         */

        RfcHandlers(IRCClient* client) : _client(client) {}

    private:
        IRCClient* _client;         ///< The IRC client
};

const RfcCommand RfcCommands[] =	///< The array of function pointers mapped to their command
{
    {"001", &RfcHandlers::Handle001},
    {0,0}
};
