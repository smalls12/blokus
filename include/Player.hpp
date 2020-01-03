#pragma once

#include <string>

#include "PlayerColor.hpp"

class Player {

public:
    Player(std::string username, std::string uuid, uint32_t playerId);
    ~Player();

    std::string getUsername();
    std::string getUuid();
    uint32_t getPlayerId();
    PlayerColor getColor();

    void Register()
    {
        if (!mRegistered)
        {
            mRegistered = true;
        }
        else
        {
            
        }
    }
    bool isRegistered() { return mRegistered; }

private:
    std::string mUsername;
    std::string mUuid;
    uint32_t mPlayerId;
    PlayerColor mColor;

    bool mRegistered;
};