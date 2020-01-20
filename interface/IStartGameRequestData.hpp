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

        virtual void SetPlayers(std::vector<std::pair<std::string, PlayerId>> players) = 0;
        virtual std::vector<std::pair<std::string, PlayerId>> GetPlayers() = 0;
};