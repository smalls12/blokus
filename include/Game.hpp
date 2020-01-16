#pragma once

#include "IGameSettings.hpp"
#include "GameMode.hpp"
#include "GameConfiguration.hpp"

#include "spdlog/spdlog.h"

class Game : public IGameSettings
{
    public:
        Game();
        ~Game();

        void SetGameMode(GameMode mode) { mMode = mode; }
        GameMode GetGameMode() { return mMode; }

        void SetGameConfiguration(GameConfiguration configuration) { mConfiguration = configuration; }
        GameConfiguration GetGameConfiguration() { return mConfiguration; }

        void SetUsername(std::string username) { mUsername = username; }
        std::string GetUsername() { return mUsername; }

        void SetGameName(std::string gameName) { mGameName = gameName; }
        std::string GetGameName() { return mGameName; }

        void SetServer(std::string server) { mServer = server; }
        std::string GetServer() { return mServer; }        

    private:
        GameMode            mMode;
        GameConfiguration   mConfiguration;
        std::string         mUsername;
        std::string         mGameName;
        std::string         mServer;
};