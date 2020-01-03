#include "PlayerManager.hpp"

#include "spdlog/spdlog.h"

PlayerManager::PlayerManager()
:   mPlayers(),
    mPlayersMutex()
{
    spdlog::get("console")->info("PlayerManager::PlayerManager");
}

PlayerManager::~PlayerManager()
{
    spdlog::get("console")->info("PlayerManager::~PlayerManager");
}

bool PlayerManager::GetPlayer(std::string uuid, std::shared_ptr<Player>& player)
{
    std::unique_lock<std::mutex> lock(mPlayersMutex);
    std::map<std::string, std::shared_ptr<Player>>::iterator it;

    it = mPlayers.find(uuid);
    if (it != mPlayers.end())
    {
        player = mPlayers[uuid];
        return true;
    }
    return false;
}

std::vector<std::shared_ptr<Player>> PlayerManager::GetListOfPlayers()
{
    std::unique_lock<std::mutex> lock(mPlayersMutex);
    std::vector<std::shared_ptr<Player>> activeGames;
    std::map<std::string, std::shared_ptr<Player>>::iterator it;

    for ( it = mPlayers.begin(); it != mPlayers.end(); it++ )
    {
        activeGames.push_back(it->second);
    }

    return activeGames;
}

bool PlayerManager::AddPlayerToGame(std::string uuid, std::shared_ptr<Player> player)
{
    std::unique_lock<std::mutex> lock(mPlayersMutex);
    mPlayers.insert( std::pair<std::string, std::shared_ptr<Player>>(uuid, player) );
    return true;
}

bool PlayerManager::RemovePlayerFromGame(std::string uuid)
{
    std::unique_lock<std::mutex> lock(mPlayersMutex);
    std::map<std::string, std::shared_ptr<Player>>::iterator it;

    it = mPlayers.find(uuid);
    if (it != mPlayers.end())
    {
        mPlayers.erase(uuid);
        return true;
    }
    return false;
}

bool PlayerManager::RegisterPlayer(blokus::Message in)
{
    blokus::Message out;
    return RegisterPlayer(in, out);
}

bool PlayerManager::RegisterPlayer(blokus::Message in, blokus::Message& out)
{
    spdlog::get("console")->info("PlayerManager::RegisterPlayer() - Start");

    if (in.request().type() == blokus::REGISTER)
    {
        std::string uuid;
        if (in.type() == blokus::Message::REQUEST)
        {
            uuid = in.request().register_req().uuid();
        }
        else if (in.type() == blokus::Message::RESPONSE)
        {
            uuid = in.response().register_resp().uuid();
        }

        std::shared_ptr<Player> player;
        if ( GetPlayer(uuid, player) )
        {
            if ( player )
            {
                player->Register();
                spdlog::get("console")->info("PlayerManager::RegisterPlayer() - Player {} registered!", uuid);
            }
            else
            {
                spdlog::get("stderr")->error("PlayerManager::RegisterPlayer() - Player {} not found!", uuid);
            }
        }
        else
        {
            spdlog::get("stderr")->error("PlayerManager::RegisterPlayer() - Player {} does not exist, cannot register.", uuid);
        }
    }

    spdlog::get("console")->info("PlayerManager::RegisterPlayer() - Done");

    return true;
}