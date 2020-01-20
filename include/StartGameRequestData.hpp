#pragma once

/* =========================================================
 *
 * StartGameRequestData.hpp
 * 
 * Concrete implementation for that data to build the
 * game request
 * 
 * ========================================================= */

#include "IStartGameRequestData.hpp"

class StartGameRequestData : public IStartGameRequestData
{
    public:
        StartGameRequestData();
        ~StartGameRequestData();

        void SetGameConfiguration(GameConfiguration config) { mGameConfiguration = config; }
        GameConfiguration GetGameConfiguration() { return mGameConfiguration; }

        void SetPlayers(std::vector<std::pair<std::string, PlayerId>> players) { mPlayers = players; }
        std::vector<std::pair<std::string, PlayerId>> GetPlayers() { return mPlayers; }

    private:
        GameConfiguration                                   mGameConfiguration;
        std::vector<std::pair<std::string, PlayerId>>       mPlayers;
};