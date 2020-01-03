#include "ActiveGameManager.hpp"

#include "spdlog/spdlog.h"

ActiveGameManager::ActiveGameManager()
:   mActiveGames(),
    mActiveGamesMutex()
{
    spdlog::get("console")->info("ActiveGameManager::ActiveGameManager");
}

ActiveGameManager::~ActiveGameManager()
{
    spdlog::get("console")->info("ActiveGameManager::~ActiveGameManager");
}

std::vector<std::shared_ptr<ActiveGame>> ActiveGameManager::GetListOfActiveGames()
{
    std::unique_lock<std::mutex> lock(mActiveGamesMutex);
    std::vector<std::shared_ptr<ActiveGame>> activeGames;
    std::map<std::string, std::shared_ptr<ActiveGame>>::iterator it;

    for ( it = mActiveGames.begin(); it != mActiveGames.end(); it++ )
    {
        activeGames.push_back(it->second);
    }

    return activeGames;
}

bool ActiveGameManager::GameAlreadyActive(std::string name, std::shared_ptr<ActiveGame> activeGame)
{
    std::unique_lock<std::mutex> lock(mActiveGamesMutex);
    std::map<std::string, std::shared_ptr<ActiveGame>>::iterator it;

    it = mActiveGames.find(name);
    if (it != mActiveGames.end())
    {
        activeGame = mActiveGames[name];
        return true;
    }
    return false;
}

bool ActiveGameManager::AddActiveGame(std::string name, std::shared_ptr<ActiveGame> activeGame)
{
    std::shared_ptr<ActiveGame> alreadyActiveGame;
    if ( GameAlreadyActive(name, alreadyActiveGame) )
    {
        for( auto p : activeGame->GetListOfPeers() )
        {
            alreadyActiveGame->AddPeerToGame(p);
        }
    }
    else
    {
        std::unique_lock<std::mutex> lock(mActiveGamesMutex);
        mActiveGames.insert( std::pair<std::string, std::shared_ptr<ActiveGame>>(name, activeGame) );
    }

    return true;
}

bool ActiveGameManager::RemoveActiveGame(std::string name)
{
    std::unique_lock<std::mutex> lock(mActiveGamesMutex);
    std::map<std::string, std::shared_ptr<ActiveGame>>::iterator it;

    it = mActiveGames.find(name);
    if (it != mActiveGames.end())
    {
        mActiveGames.erase(name);
        return true;
    }
    return false;
}