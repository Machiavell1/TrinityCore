/**
 * @file    src\server\irc\IRCWorker.h
 *
 * @brief   Declares the irc worker class.
 */
#pragma once
#include "DelayExecutor.h"
#include <ace/Method_Request.h>

class IRCClient;

class IRCPreService : public ACE_Method_Request
{
    public:
        IRCPreService(IRCClient*& client) : _client(client) {};

        int call();

    private:
        IRCClient*& _client;
};

class IRCPostService : public ACE_Method_Request
{
    public:
        IRCPostService(IRCClient*& client) : _client(client) {};

        int call();

    private:
        IRCClient*& _client;
};

class IRCServiceRequest: public ACE_Method_Request
{
    public:
        IRCServiceRequest();
};

class IRCWorker : protected ACE_Task_Base//protected DelayExecutor
{
    public:
        IRCWorker() { ACE_Task_Base::activate(THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED); }
        int svc();

    private:
        IRCClient* _client;
};