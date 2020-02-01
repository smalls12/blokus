#pragma once

/* =========================================================
 *
 * PlayerTurnManager.hpp
 * 
 * Controls whos turn it is
 * Will change for 2 Player and 4 Player modes
 * 
 * Only in charge of moving the player id
 * 
 * Two Player Mode
 *  1 - 2 -1 - 2 - 1
 * 
 * Four Player Mode
 *  1 - 2 - 3 - 4 - 1
 * ========================================================= */

#include "IGameSettings.hpp"
#include "PlayerId.hpp"
#include "PlayerColor.hpp"

#include <vector>

class PlayerTurnManager
{
    public:
        PlayerTurnManager(IGameSettings& settings);
        ~PlayerTurnManager();

        // PlayerId NextPlayersTurn();
        std::pair<PlayerId, PlayerColor> NextPlayersTurn();

    private:
        IGameSettings&                                  mSettings;
        unsigned int                                    mCurrentPlayersTurn;
        // std::vector<PlayerId>   mPlayers;
        std::vector<std::pair<PlayerId, PlayerColor>>   mPlayers;
};