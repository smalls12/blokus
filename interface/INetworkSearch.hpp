#pragma once

/* =========================================================
 *
 * Network layer abstraction
 * Building with reference to what I know I need from zyre
 * However should be abstract enough to replace with any
 * network technology
 * 
 * ========================================================= */

#include <vector>
#include <string>

class INetworkSearch
{
    public:
        // Search for lobbies on network
        virtual void Search(std::vector<std::pair<std::string, std::string>>& lobbies) = 0;
};