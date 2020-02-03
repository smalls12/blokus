#pragma once

/* =========================================================
 *
 * PlayerScores.hpp
 * 
 * Tracks the scores for each player
 * Will change for 2 Player and 4 Player modes
 * 
 * ========================================================= */

#include "IGameSettings.hpp"
#include "PlayerId.hpp"

#include <map>

class PlayerScores
{
    public:
        PlayerScores(IGameSettings& settings);
        ~PlayerScores();

        unsigned int GetScore(PlayerId id);
        void AddToScore(PlayerId id, unsigned int score);

    private:
        IGameSettings&                          mSettings;
        std::map<PlayerId, unsigned int>        mPlayers;
};