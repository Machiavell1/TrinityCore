/**
 * @file src\server\irc\IrcMessage.h
 *
 * @brief Declares the irc message class.
 */

#pragma once

#include <string>

/**
 * @struct IrcIdent
 *
 * @brief Irc user identifier.
 *
 * @author Machiavelli
 * @date 9-2-2013
 */

struct IrcIdent
{
    /**
     * @fn void operator=(std::string string)
     *
     * @brief Assignment operator. Constructs object based on incoming string.
     *
     * @author Machiavelli
     * @date 9-2-2013
     *
     * @param string The string as received from the server.
     */

    void operator =(std::string string)
    {
        size_t p1 = string.find("!");
        size_t p2 = string.find("@");
        Nick = string.substr(0, p1 - 1);
        Ident = string.substr(p1+1, p2-1);
        Host = string.substr(p2+1);
    }

    std::string Nick;   ///< Nickname (Nickname!Ident@Host)
    std::string Ident;   ///< Ident part 
    std::string Host;   ///< The host
    std::string Full;    ///< The full string
};

/**
 * @struct IrcMessage
 *
 * @brief Irc message.
 *
 * @author Machiavelli
 * @date 9-2-2013
 */

struct IrcMessage
{
    /**
     * @fn IrcMessage(const char* data)
     *
     * @brief Constructor.
     *
     * @author Machiavelli
     * @date 9-2-2013
     *
     * @param data The data as received from the server.
     */

    IrcMessage(const char* data)
    {
        Full = std::string(data);
        size_t p1 = Full.find(" ");
        size_t p2 = Full.find(" ", p1 + 1);
        size_t p3 = Full.find(" ", p2 + 1);
        size_t p4 = Full.find(" ", p3 + 1); 
        size_t p5 = Full.find(":", p4+1);

        Ident = Full.substr(1, p1 - 1);
        Command = Full.substr(p1 + 1, p2 - p1 - 1);
        Channel = Full.substr(p2 + 1, p3 - p2 - 1); 
        Message = Full.substr(p3+1);
    }

    IrcIdent Ident;         ///< Sender of the message
    std::string Command;	///< The command
    std::string Channel;	    ///< The channel. Can be username too in case of private message
    std::string Message;	///< The message parameters

    std::string Full;        ///< Full copy of the disected string
};