#include "IRCWorker.h"
#include "IRCClient.h"
#include "Util.h"

int IRCPreService::call()
{
    _client = new IRCClient();
    return 0;
}

int IRCPostService::call()
{
    _client->Quit("IRCPostService::call()");
    
    // Perhaps the deletion of the _client object should be done async as well
    // because deleting the object while it might be running an async operation
    // is bad.
    delete _client;
    _client = NULL;
    return 0;
}

int IRCWorker::svc()
{
    IRCClient* client = new IRCClient();

    char* buf = new char[2048];
    int bytes = -1;
    std::stringstream ss;
    for (;;)
    {
        bytes = client->Recv(buf);
        bool more = false;
        if (bytes > 0)
        {
            buf[bytes] = '\0';
            if (bytes == 2047)
                more = true;

            std::string bufcontents = ss.str() + buf;
            ss.str("");
            Tokenizer tokens(bufcontents, '\n');
            uint32 lineCount = tokens.size();
            uint32 curLine = 0;
            for (Tokenizer::const_iterator itr = tokens.begin(); itr != tokens.end(); ++itr)
            {
                const char* line = (*itr);
                printf(line);
                printf("\n");
                if ((curLine++ < tokens.size()-1 && more) || !more)
                    client->HandleMessage(line);
                else    // save in buffer for next read
                    ss << line;
            }

            /*while (line != NULL)
            {
                printf(line);
                printf("\n");
                char* one = strdup(line);
                client->HandleMessage(one);
                free(one);
                line = strtok(buf, "\r\n");
            }*/
        }
        else if (bytes == -1)
        {
            delete client;
            client = new IRCClient();
        }
    }

    delete[] buf;
    delete client;
}
