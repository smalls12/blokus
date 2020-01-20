#pragma once

#include "GameConfiguration.hpp"
#include "Player.hpp"

#include <vector>
#include <memory>

class IStartGameRequestData
{
    public:

        virtual void SetGameConfiguration(GameConfiguration config) = 0;
        virtual GameConfiguration GetGameConfiguration() = 0;

        virtual void SetPlayers(std::vector<std::shared_ptr<Player>> players) = 0;
        virtual std::vector<std::shared_ptr<Player>> GetPlayers() = 0;
};