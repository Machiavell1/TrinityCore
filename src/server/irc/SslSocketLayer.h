#pragma once
#include "BaseSocketLayer.h"

/**
 * @class SslSocketLayer
 *
 * @brief Ssl socket layer. Currently does not do anything yet because
 * 		  I haven't been able to get ACE to compile with included SSL files
 *
 * @author Machiavelli
 * @date 6-2-2013
 */

class SslSocketLayer : public BaseSocketLayer
{
    public:
        bool Connect(char const* hostname, uint16 port);
};