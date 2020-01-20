#pragma once

#include "PlayerId.hpp"

#include <string>
#include <ostream>

class Player {

public:
    Player(std::string username, std::string uuid);
    ~Player();

    std::string getUsername() { return mUsername; }
    std::string getUuid() { return mUuid; }
    PlayerId getPlayerId() { return mPlayerId; }

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
    
    void AssignPlayerID(unsigned int id)
    {
        switch(id)
        {
            case 1:
            {
                mPlayerId = PlayerId::PLAYER_ONE;
                break;
            }
            case 2:
            {
                mPlayerId = PlayerId::PLAYER_TWO;
                break;
            }
            case 3:
            {
                mPlayerId = PlayerId::PLAYER_THREE;
                break;
            }
            case 4:
            {
                mPlayerId = PlayerId::PLAYER_FOUR;
                break;
            }
            default:
            {
                mPlayerId = PlayerId::UNASSIGNED;
                break;
            }
        }
    }

    void AssignPlayerID(PlayerId id) { mPlayerId = id; }

    friend std::ostream& operator <<(std::ostream& outputStream, const Player& player);

private:
    std::string mUsername;
    std::string mUuid;
    PlayerId mPlayerId;

    bool mRegistered;
};