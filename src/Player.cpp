#include <Player.hpp>

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