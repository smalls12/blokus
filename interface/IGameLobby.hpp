#pragma once

/* =========================================================
 *
 * IGameLobby.hpp
 * 
 * ========================================================= */

#include <string>

class IGameLobby
{
    public:
        virtual bool SendMessageToLobby(std::string data) = 0;

};