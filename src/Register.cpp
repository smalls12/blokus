#include "Register.hpp"

Register::Register()
:   mPlayerColor(PlayerColor::BLUE),
    mPlayerId(PlayerId::PLAYER_ONE)
{
    spdlog::get("console")->debug("Register::Register");
}

Register::~Register()
{
    spdlog::get("console")->debug("Register::~Register");
}