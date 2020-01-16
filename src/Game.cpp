#include "Game.hpp"

Game::Game()
:   mMode(GameMode::CLOSE),
    mConfiguration(GameConfiguration::TWO_PLAYER),
    mUsername(std::string("Default")),
    mGameName(std::string("BLOKUS")),
    mServer(std::string(""))
{
    spdlog::get("console")->info("Game::Game");
}

Game::~Game()
{
    spdlog::get("console")->info("Game::~Game");
}