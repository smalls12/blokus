#pragma once

/* =========================================================
 *
 * GameFlowManager.hpp
 * 
 * Controls whos turn it is
 * Will change for 2 Player and 4 Player modes
 * 
 * ========================================================= */

#include "IGameSettings.hpp"
#include "PlayerId.hpp"

#include <vector>

class GameFlowManager
{
    public:
        GameFlowManager(IGameSettings& settings);
        ~GameFlowManager();

        PlayerId NextPlayersTurn();

    private:
        IGameSettings&          mSettings;
        unsigned int            mCurrentPlayersTurn;
        std::vector<PlayerId>   mPlayers;
};