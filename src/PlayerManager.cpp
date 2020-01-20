#include "PlayerManager.hpp"

#include "Register.hpp"

#include "spdlog/spdlog.h"

PlayerManager::PlayerManager(RegisterResponse& registerResponse)
:   mRegisterResponse(registerResponse),
    mPlayers(),
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
    spdlog::get("console")->info("PlayerManager::AddPlayerToGame() - Add Player {}", uuid);

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

bool PlayerManager::RemovePlayerFromGame(IRegistrationUnsuccessful& request)
{
    std::unique_lock<std::mutex> lock(mPlayersMutex);
    std::map<std::string, std::shared_ptr<Player>>::iterator it;

    it = mPlayers.find(request.GetUuid());
    if (it != mPlayers.end())
    {
        mPlayers.erase(request.GetUuid());
        return true;
    }
    return false;
}

bool PlayerManager::RegisterLocalPlayer(IRegistrationSuccessful& request)
{
    spdlog::get("console")->info("PlayerManager::RegisterLocalPlayer() - Register");

    std::shared_ptr<Player> player;
    if ( GetPlayer(request.GetUuid(), player) )
    {
        if ( player )
        {
            player->Register();
            spdlog::get("console")->info("PlayerManager::RegisterLocalPlayer() - Player {} registered!", request.GetUuid());
        }
        else
        {
            spdlog::get("stderr")->error("PlayerManager::RegisterLocalPlayer() - Player {} not found!", request.GetUuid());
        }
    }
    else
    {
        spdlog::get("stderr")->error("PlayerManager::RegisterLocalPlayer() - Player {} does not exist, cannot register.", request.GetUuid());
    }

    spdlog::get("console")->info("PlayerManager::RegisterLocalPlayer() - Done");

    return true;
}

bool PlayerManager::RegisterRemotePlayer(IRegisterRequest& request)
{
    spdlog::get("console")->info("PlayerManager::RegisterRemotePlayer() - Register");

    std::shared_ptr<Player> player;
    if ( GetPlayer(request.GetUuid(), player) )
    {
        if ( player )
        {
            player->Register();
            spdlog::get("console")->info("PlayerManager::RegisterRemotePlayer() - Player {} registered!", request.GetUuid());

            // the player manager will assign colors and player ids based off of who came first

            Register r;
            r.SetPlayerColor(PlayerColor::BLUE);
            r.SetPlayerId(PlayerId::PLAYER_ONE);
            r.SetUsername(request.GetUsername());
            r.SetUuid(request.GetUuid());
            mRegisterResponse.SendRegistrationSuccessfulResponse(r);
        }
        else
        {
            spdlog::get("stderr")->error("PlayerManager::RegisterRemotePlayer() - Player {} not found!", request.GetUuid());
        }
    }
    else
    {
        spdlog::get("stderr")->error("PlayerManager::RegisterRemotePlayer() - Player {} does not exist, cannot register.", request.GetUuid());
    }

    spdlog::get("console")->info("PlayerManager::RegisterRemotePlayer() - Done");

    return true;
}
