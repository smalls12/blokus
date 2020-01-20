#include "PlayerManager.hpp"

#include "Register.hpp"

#include <sstream>

#include "spdlog/spdlog.h"

PlayerManager::PlayerManager(RegisterResponse& registerResponse)
:   mRegisterResponse(registerResponse),
    mLocalPlayerUniqueIdentifier(),
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

std::vector<std::shared_ptr<Player>> PlayerManager::GetListOfPlayers() const
{
    std::unique_lock<std::mutex> lock(mPlayersMutex);
    std::vector<std::shared_ptr<Player>> activeGames;
    std::map<std::string, std::shared_ptr<Player>>::const_iterator it;

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

bool PlayerManager::AddLocalPlayerToGame(std::string uuid, std::shared_ptr<Player> player)
{
    spdlog::get("console")->info("PlayerManager::AddLocalPlayerToGame() - Add Local Player {}", uuid);

    mLocalPlayerUniqueIdentifier = uuid;

    AddPlayerToGame(uuid, player);
 
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

bool PlayerManager::RegisterPlayer(IRegistrationSuccessful& request)
{
    spdlog::get("console")->info("PlayerManager::RegisterPlayer() - Register");

    std::shared_ptr<Player> player;
    if ( GetPlayer(request.GetUuid(), player) )
    {
        if ( player )
        {
            player->Register();
            spdlog::get("console")->info("PlayerManager::RegisterPlayer() - Player {} registered!", request.GetUuid());
        }
        else
        {
            spdlog::get("stderr")->error("PlayerManager::RegisterPlayer() - Player {} not found!", request.GetUuid());
        }
    }
    else
    {
        spdlog::get("stderr")->error("PlayerManager::RegisterPlayer() - Player {} does not exist, cannot register.", request.GetUuid());
    }

    spdlog::get("console")->info("PlayerManager::RegisterPlayer() - Done");

    return true;
}

bool PlayerManager::RegisterPlayer(IRegisterRequest& request)
{
    spdlog::get("console")->info("PlayerManager::RegisterPlayer() - Register");

    std::shared_ptr<Player> player;
    if ( GetPlayer(request.GetUuid(), player) )
    {
        if ( player )
        {
            player->Register();
            spdlog::get("console")->info("PlayerManager::RegisterPlayer() - Player {} registered!", request.GetUuid());

            // the player manager will assign colors and player ids based off of who came first

            Register r;
            r.SetUsername(request.GetUsername());
            r.SetUuid(request.GetUuid());
            mRegisterResponse.SendRegistrationSuccessfulResponse(r);
        }
        else
        {
            spdlog::get("stderr")->error("PlayerManager::RegisterPlayer() - Player {} not found!", request.GetUuid());
        }
    }
    else
    {
        spdlog::get("stderr")->error("PlayerManager::RegisterPlayer() - Player {} does not exist, cannot register.", request.GetUuid());
    }

    spdlog::get("console")->info("PlayerManager::RegisterPlayer() - Done");

    return true;
}

std::ostream& operator <<(std::ostream& outputStream, const PlayerManager& playerManager)
{
    outputStream << "\n===== Players =====\n";

    for( auto p : playerManager.GetListOfPlayers() )
    {
        std::stringstream sstream;
        sstream << *p;
        outputStream << sstream.str();
    }
    
    outputStream << "\n===== Players =====\n";

    return outputStream;
}