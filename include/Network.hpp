#pragma once

/* =========================================================
 *
 * Implements the network layer
 * 
 * ========================================================= */

#include "INetworkConnection.hpp"
#include "INetworkConfigure.hpp"
#include "INetworkLobby.hpp"
#include "INetworkSend.hpp"
#include "INetworkReceive.hpp"
#include "INetworkSearch.hpp"

extern "C" {
// encapsulate zyre
#include "zyre.h"
}

#include <string>

class Network : public INetworkConnection, public INetworkConfigure, public INetworkLobby, public INetworkSend, public INetworkReceive, public INetworkSearch
{
    public:
        Network(std::string nodeName);
        ~Network();

        // Connect into the network
        bool Connect() override;

        // Disconnect from the network
        void Disconnect() override;

        // Represents any steps required after connecting
        bool Start() override;

        // Represents any steps required prior to disconnecting
        void Stop() override;

        // Configure a network
        bool Configure(std::string parameter) override;

        // Retrieve the name of the network
        std::string GetName() override;

        // Retrieve the unique identifier of the network
        std::string GetUniqueIdentifier() override;

        // Join a network lobby
        bool JoinGroup(std::string groupName) override;

        // Leave a network lobby
        bool LeaveGroup(std::string groupName) override;

        // Send to the network
        int Send(std::string groupName, std::string message) override;

        bool Poll() override;

        // Receive from the network
        // bool Receive(std::string groupName, GameNotification& notification) override;

        // Receive from the network
        //
        // Format for this implementation
        // <1>  NAME
        // <2>  UUID
        // <3>  TYPE
        // <4>  DATA
        bool Receive(std::string groupName, std::vector<std::string>& messages) override;

        // Search for lobbies on network
        void Search(std::vector<std::pair<std::string, std::string>>& lobbies) override;
    
    private:
        std::string     mNodeName;
        zyre_t          *mNode;
        zpoller_t       *mPoller;
};