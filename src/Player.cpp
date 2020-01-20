#include <Player.hpp>

#include "PlayerIdString.hpp"

Player::Player(std::string username, std::string uuid)
:   mUsername(username),
    mUuid(uuid),
    mPlayerId(PlayerId::UNASSIGNED)
{

}

Player::~Player()
{
    // nothing
}

std::ostream& operator <<(std::ostream& outputStream, const Player& player)
{
    outputStream << "\n===== Player =====\n";
    outputStream << player.mUsername;
    outputStream << "\n";
    outputStream << player.mUuid;
    outputStream << "\n";
    outputStream << PlayerIdString::PrintPlayerIdString(player.mPlayerId);
    outputStream << "\n===== Player =====\n";

    return outputStream;
}