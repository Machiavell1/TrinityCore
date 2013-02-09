#pragma once

#include "Common.h"

class BaseSocketLayer
{
    public:
        virtual bool Connect(char const* hostname, uint16 port) = 0;
        virtual void Disconnect() = 0;
        virtual bool Send(const char* data) = 0;
        //virtual bool SendRaw(const char* data) = 0;
        virtual int Recv(char* buf) = 0;
};