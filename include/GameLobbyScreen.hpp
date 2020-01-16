#pragma once

#include "IGameSettings.hpp"
#include "MessageProcessor.hpp"
#include "ReadGameNotification.hpp"
#include "PlayerManager.hpp"
#include "RegisterResponse.hpp"

#include <map>
#include <vector>

class GameLobbyScreen
{
    public:
        GameLobbyScreen(IGameSettings& settings,
                        MessageProcessor& messageProcessor,
                        ReadGameNotification& readGameNotification,
                        PlayerManager& playerManager);
        ~GameLobbyScreen();

        bool ReadyToStart();
        void Show();

    protected:
        bool mReadyToStart;

        IGameSettings&              mSettings;
        MessageProcessor&           mMessageProcessor;
        ReadGameNotification&       mReadGameNotification;
        PlayerManager&              mPlayerManager;

    private:
        virtual void UpdateReadyToStart();
        virtual void DrawGameMode();
        virtual void DrawReadyToStart();

        void UpdatePlayersInLobby();
        void UpdateCircleGraphic();
        void UpdateGameLobbyScreen();
        void DrawGameLobbyScreen();
        void DrawCircleGraphic();
        void DrawPlayersInLobby();
        void ParseMessage(GameNotification gn);
        void CheckForNotification();
        void UpdateGameLobbyDrawFrame();
};