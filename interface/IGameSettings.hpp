#pragma once

/* =========================================================
 *
 * IGamepp
 * 
 * ========================================================= */

#include "GameMode.hpp"
#include "GameConfiguration.hpp"

#include <string>

class IGameSettings
{
    public:
        virtual GameMode GetGameMode() = 0;
        virtual void SetGameConfiguration(GameConfiguration configuration) = 0;
        virtual std::string GetGameName() = 0;
};