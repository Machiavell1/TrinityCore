#pragma once

#include <string>

struct IrcIdent
{
    void operator =(std::string string)
    {
        size_t p1 = string.find("!");
        size_t p2 = string.find("@");
        Nick = string.substr(0, p1 - 1);
        Ident = string.substr(p1+1, p2-1);
        Host = string.substr(p2+1);
    }

    std::string Nick;
    std::string Ident;
    std::string Host;
    std::string Full;
};

struct IrcMessage
{
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

    IrcIdent Ident;
    std::string Command;
    std::string Channel;
    std::string Message;

    std::string Full;
};