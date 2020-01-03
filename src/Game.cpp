#include "Game.hpp"

Game::Game()
:   mMode(GameMode::CLOSE),
    mUsername(std::string("Default")),
    mGameName(std::string("BLOKUS")),
    mServer(std::string(""))
{
    spdlog::get("console")->info("Game::Game");
}

Game::Game(GameMode mode, std::string userName, std::string gameName, std::string server)
:   mMode(mode),
    mUsername(userName),
    mGameName(gameName),
    mServer(server)
{
    spdlog::get("console")->info("Game::Game");
}

Game::~Game()
{
    spdlog::get("console")->info("Game::~Game");
}