#pragma once

#include "GameMode.hpp"

#include "spdlog/spdlog.h"

class Game
{
    public:
        Game();
        Game(GameMode mode, std::string userName, std::string gameName, std::string server);
        ~Game();

        // overload function call
        void operator()()
        {
            spdlog::get("console")->debug("Game::operator() - Start");

            spdlog::get("console")->debug("Game::operator() - Done");

            return;
        }

        GameMode GetGameMode() { return mMode; }
        std::string GetUsername() { return mUsername; }
        std::string GetGameName() { return mGameName; }
        std::string GetServer() { return mServer; }

    private:
        GameMode        mMode;
        std::string     mUsername;
        std::string     mGameName;
        std::string     mServer;
};