#pragma once

#include "Player.hpp"

#include <vector>
#include <memory>

class IPlayerRegistry
{
    public:

        virtual std::vector<std::shared_ptr<Player>> GetListOfPlayers() const = 0;
};