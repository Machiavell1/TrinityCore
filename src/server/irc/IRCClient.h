#pragma once
#include "BaseSocketLayer.h"
#include "RfcHandlers.h"

class IRCClient
{
    friend class IRCPreService;
    friend class IRCPostService;
    friend class IRCServiceRequest;
    friend class RfcHandlers;
    friend class IRCWorker;

    protected:
        IRCClient();
        ~IRCClient();

        void HandleMessage(const char* data);

        void Join(const char* channel, const char* key = NULL);
        void Part(const char* channel, const char* message = NULL);
        void Quit(const char* quitMsg = "IRCClient::_defaultQuitMsg");
        void Nick(const char* nick);

        void Send(const char* data, ...);
        int Recv(char* buf);

    private:
        BaseSocketLayer* _socket;
        RfcHandlers _handlers;
};