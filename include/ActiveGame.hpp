#pragma once

#include <string>
#include <vector>
#include <mutex>
#include <memory>

class ActiveGame
{
    public:
        ActiveGame(std::string name, std::string server);
        ~ActiveGame();

        std::string GetGameName() { return mName; }
        std::string GetServer() { return mServer; }
        
        bool FindPeer(std::string name);
        std::vector<std::string> GetListOfPeers();
        bool AddPeerToGame(std::string peer);
        bool RemovePeerFromGame(std::string name);

    private:
        std::string                 mName;
        std::string                 mServer;
        std::vector<std::string>    mPeersInGame;
        std::mutex                  mPeersInGameMutex;
};