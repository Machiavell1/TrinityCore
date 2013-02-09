/**
 * @file    src\server\irc\IRCWorker.h
 *
 * @brief   Declares the irc worker class.
 */
#pragma once
#include "DelayExecutor.h"
#include <ace/Method_Request.h>

class IRCClient;

/**
 * @class IRCPreService
 *
 * @brief Pre-service hook class.
 *
 * @author Machiavelli
 * @date 9-2-2013
 */

class IRCPreService : public ACE_Method_Request
{
    public:

        /**
         * @fn IRCPreService::IRCPreService(IRCClient*& client)
         *
         * @brief Constructor.
         *
         * @author Machiavelli
         * @date 9-2-2013
         *
         * @param client Pointer to IRC client object to be operated on.
         */

        IRCPreService(IRCClient*& client) : _client(client) {};

        int call();

    private:
        IRCClient*& _client;
};

class IRCPostService : public ACE_Method_Request
{
    public:

        /**
         * @fn IRCPostService::IRCPostService(IRCClient*& client)
         *
         * @brief Constructor.
         *
         * @author Machiavelli
         * @date 9-2-2013
         *
         * @param [in,out] client If non-null, the client.
         */

        IRCPostService(IRCClient*& client) : _client(client) {};

        int call();

    private:
        IRCClient*& _client;	///< The client
};

class IRCServiceRequest: public ACE_Method_Request
{
    public:

        /**
         * @fn IRCServiceRequest::IRCServiceRequest();
         *
         * @brief Default constructor.
         *
         * @author Machiavelli
         * @date 9-2-2013
         */

        IRCServiceRequest();
};

class IRCWorker : protected ACE_Task_Base//protected DelayExecutor
{
    public:

        /**
         * @fn IRCWorker::IRCWorker()
         *
         * @brief Default constructor.
         *
         * @author Machiavelli
         * @date 9-2-2013
         */

        IRCWorker() { ACE_Task_Base::activate(THR_NEW_LWP | THR_JOINABLE | THR_INHERIT_SCHED); }
        int svc();

    private:
        IRCClient* _client; ///< The client
};