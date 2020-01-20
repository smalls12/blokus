extern "C" {
#include "raylib.h"
#include "raygui.h"
}

#include "StartGameLobbyScreen.hpp"

namespace
{
    static const int screenWidth = 800;
    static const int screenHeight = 450;
}

StartGameLobbyScreen::StartGameLobbyScreen( IGameSettings& settings,
                                            MessageProcessor& messageProcessor,
                                            ReadGameNotification& readGameNotification,
                                            PlayerManager& playerManager,
                                            StartGame& startGame,
                                            IRandomizePlayerIds& randomizePlayerIds)
:   GameLobbyScreen(settings, messageProcessor, readGameNotification, playerManager),
    mStartGame(startGame),
    mRandomizePlayerIds(randomizePlayerIds),
    mFourPlayerMode(false),
    mStartGameButton(false)
{
    spdlog::get("console")->debug("StartGameLobbyScreen::StartGameLobbyScreen()");
}

StartGameLobbyScreen::~StartGameLobbyScreen()
{
    spdlog::get("console")->debug("StartGameLobbyScreen::~StartGameLobbyScreen()");
}

void StartGameLobbyScreen::UpdateReadyToStart()
{
    if (mStartGameButton)
    {
        spdlog::get("console")->debug("StartGameLobbyScreen::UpdateReadyToStart() - Start!");

        mRandomizePlayerIds.Randomize();
        mStartGame.Start(mSettings, mPlayerManager);
        mReadyToStart = true;
    }
}

void StartGameLobbyScreen::DrawGameMode()
{
    mFourPlayerMode = GuiCheckBox((Rectangle){ 100, screenHeight - 20, 12, 12 }, "4-Player Mode ( Default 2 )", mFourPlayerMode);
}

void StartGameLobbyScreen::DrawReadyToStart()
{
    if( !mFourPlayerMode )
    {
        if( mPlayerManager.GetListOfPlayers().size() == 2 )
        {
            spdlog::get("console")->trace("StartGameLobbyScreen::DrawReadyToStart() - Ready to start!");
            mStartGameButton = GuiButton((Rectangle){ screenWidth / 2 + 100, screenHeight - 100, 125, 30 }, "START"); 
        }
        else
        {
            spdlog::get("console")->trace("StartGameLobbyScreen::DrawReadyToStart() - Not ready to start");
        }
    }
    else
    {
        if( mPlayerManager.GetListOfPlayers().size() == 4 )
        {
            spdlog::get("console")->trace("StartGameLobbyScreen::DrawReadyToStart() - Ready to start!");
            mStartGameButton = GuiButton((Rectangle){ screenWidth / 2 + 100, screenHeight - 100, 125, 30 }, "START"); 
        }
        else
        {
            spdlog::get("console")->trace("StartGameLobbyScreen::DrawReadyToStart() - Not ready to start");
        }
    }
}