#include "RegisterForGame.hpp"

RegisterForGame::RegisterForGame(NetworkConnection& connection, std::string gameName)
:   mConnection(connection),
    mGameName(gameName)
{
    spdlog::get("console")->debug("RegisterForGame::RegisterForGame");
}

RegisterForGame::~RegisterForGame()
{
    spdlog::get("console")->debug("RegisterForGame::~RegisterForGame");
}