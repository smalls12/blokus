#include "ActiveGame.hpp"

#include "spdlog/spdlog.h"

ActiveGame::ActiveGame(std::string name, std::string server)
:   mName(name),
    mServer(server),
    mPeersInGame(),
    mPeersInGameMutex()
{
    spdlog::get("console")->debug("ActiveGame::ActiveGame");
}

ActiveGame::~ActiveGame()
{
    spdlog::get("console")->debug("ActiveGame::~ActiveGame");
}

bool ActiveGame::FindPeer(std::string name)
{
    std::unique_lock<std::mutex> lock(mPeersInGameMutex);
    std::vector<std::string>::iterator it;
    it = find(mPeersInGame.begin(), mPeersInGame.end(), name);
    if (it != mPeersInGame.end())
    {
        return true;
    }
    
    return false;
}

std::vector<std::string> ActiveGame::GetListOfPeers()
{
    std::unique_lock<std::mutex> lock(mPeersInGameMutex);
    return mPeersInGame;
}

bool ActiveGame::AddPeerToGame(std::string name)
{
    if( !FindPeer(name) )
    {
        std::unique_lock<std::mutex> lock(mPeersInGameMutex);
        mPeersInGame.push_back(name);
        return true;
    }

    return false;
}

bool ActiveGame::RemovePeerFromGame(std::string name)
{
    std::unique_lock<std::mutex> lock(mPeersInGameMutex);
    std::vector<std::string>::iterator it;
    it = find(mPeersInGame.begin(), mPeersInGame.end(), name);
    if (it != mPeersInGame.end())
    {
        mPeersInGame.erase(it);
        return true;
    }
    
    return false;        
}