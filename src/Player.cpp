#include <Player.hpp>

Player::Player(std::string username, std::string uuid, uint32_t playerId)
:   mUsername(username),
    mUuid(uuid),
    mPlayerId(playerId)
{
    switch(mPlayerId)
    {
        case 0:
            mColor = PlayerColor::BLUE;
            break;
        case 1:
            mColor = PlayerColor::RED;
            break;
        case 2:
            mColor = PlayerColor::GREEN;
            break;
        case 3:
            mColor = PlayerColor::YELLOW;
            break;
    }
}

Player::~Player()
{
    // nothing
}

std::string Player::getUsername()
{
    return mUsername;
}

std::string Player::getUuid()
{
    return mUuid;
}

uint32_t Player::getPlayerId()
{
    return mPlayerId;
}

PlayerColor Player::getColor()
{
    return mColor;
}