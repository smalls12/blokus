#pragma once

#include "GameMode.hpp"
#include "MessageProcessor.hpp"
#include "ReadGameNotification.hpp"
#include "PlayerManager.hpp"
#include "RegisterResponse.hpp"

#include <map>
#include <vector>

class GameLobbyScreen
{
    public:
        GameLobbyScreen(GameMode mode,
                        MessageProcessor& messageProcessor,
                        ReadGameNotification& readGameNotification,
                        PlayerManager& playerManager);
        ~GameLobbyScreen();

        void Show();

    private:
        void UpdatePlayersInLobby();
        void UpdateCircleGraphic();
        void UpdateGameLobbyScreen();
        void DrawGameLobbyScreen();
        void DrawCircleGraphic();
        void DrawPlayersInLobby();
        void DrawGameMode();
        void ParseMessage(GameNotification gn);
        void CheckForNotification();
        void UpdateGameLobbyDrawFrame();

        GameMode                    mMode;
        MessageProcessor&           mMessageProcessor;
        ReadGameNotification&       mReadGameNotification;
        PlayerManager&              mPlayerManager;
};