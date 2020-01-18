extern "C" {
#include "raylib.h"

#define RAYGUI_STATIC
#include "raygui.h"
}

#include "GameLobbyScreen.hpp"
#include "NotificationTypeString.hpp"
#include "Message.hpp"

#include "spdlog/spdlog.h"

#include <vector>
#include <iostream>

#define MAX_INPUT_CHARS     9

namespace
{
    static const int screenWidth = 800;
    static const int screenHeight = 450;

    typedef struct {
        Vector2 position;
        float radius;
        float alpha;
        float speed;
        Color color;
    } CircleWave;

    CircleWave circle;

    Rectangle PlayersInGameBackground = { screenWidth / 2, 0, screenWidth, screenHeight };

    int ListView000ScrollIndex = 0;
    int ListView000Active = 0;
}

GameLobbyScreen::GameLobbyScreen(IGameSettings& settings,
                                 MessageProcessor& messageProcessor,
                                 ReadGameNotification& readGameNotification,
                                 PlayerManager& playerManager)
:   mReadyToStart(false),
    mSettings(settings),
    mMessageProcessor(messageProcessor),
    mReadGameNotification(readGameNotification),
    mPlayerManager(playerManager)
{
    spdlog::get("console")->info("GameLobbyScreen::GameLobbyScreen() - Start");
}

GameLobbyScreen::~GameLobbyScreen()
{
    spdlog::get("console")->info("GameLobbyScreen::~GameLobbyScreen() - Start");
}

bool GameLobbyScreen::ReadyToStart()
{
    mReadyToStart = true;
}

void GameLobbyScreen::UpdateReadyToStart()
{
    // not implemented
}

void GameLobbyScreen::UpdatePlayersInLobby()
{
    std::vector<std::shared_ptr<Player>> listOfPlayers = mPlayerManager.GetListOfPlayers();
    for( auto p : listOfPlayers )
    {
        Rectangle player = { screenWidth - 240, screenHeight - 100, 200, 25 };
        DrawRectangleRec(player, LIGHTGRAY);
        DrawRectangleLines(player.x, player.y, player.width, player.height, DARKGRAY);
        DrawText(p->getUuid().c_str(), player.x + 5, player.y + 8, 10, MAROON);
    }
}

void GameLobbyScreen::UpdateCircleGraphic()
{
    // Color circles animation
    circle.alpha += circle.speed;
    circle.radius += circle.speed*10.0f;

    if (circle.alpha > 1.0f) circle.speed *= -1;

    if (circle.alpha <= 0.0f)
    {
        circle.alpha = 0.0f;
        circle.radius = GetRandomValue(10, 15);
        circle.position.x = 50;
        circle.position.y = 140;
        circle.color = (Color){ 230, 41, 55, 255 };
        circle.speed = 100/2000.0f;
    }
}

void GameLobbyScreen::UpdateGameLobbyScreen()
{
    UpdateReadyToStart();
    UpdateCircleGraphic();
    UpdatePlayersInLobby();
}

void GameLobbyScreen::DrawCircleGraphic()
{
    DrawCircleV(circle.position, circle.radius, Fade(circle.color, circle.alpha));

    Rectangle rectangle = { 100, 135, 360, 220 };
    DrawTextRec(GetFontDefault(), "Waiting for other players to join...", rectangle, 20, 1, true, GRAY);
}

void GameLobbyScreen::DrawPlayersInLobby()
{
    std::stringstream ss;
    for( auto p : mPlayerManager.GetListOfPlayers() )
    {
        ss << p->getUsername();
        ss << ";";
    }

    ListView000Active = GuiListView((Rectangle){ screenWidth / 2 + 100, 120, 240, 200 }, ss.str().c_str(), &ListView000ScrollIndex, ListView000Active);
}

void GameLobbyScreen::DrawGameMode()
{
    // not implemented
}

void GameLobbyScreen::DrawReadyToStart()
{
    // not implemented
}

void GameLobbyScreen::DrawGameLobbyScreen()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawRectangleRec(PlayersInGameBackground, DARKGRAY);

    DrawText("Game Lobby", 80, 60, 30, GRAY);
    DrawText("Players In Game", screenWidth / 2 + 80, 60, 30, BLACK);

    DrawPlayersInLobby();
    DrawCircleGraphic();

    DrawGameMode();
    DrawReadyToStart();

    EndDrawing();
}

void GameLobbyScreen::CheckForNotification()
{
    if( mReadGameNotification.CheckEvent() )
    {
        GameNotification gn;
        if( mReadGameNotification.Receive(gn) )
        {
            std::stringstream ss;
            ss << gn;
            spdlog::get("console")->trace("GameLobbyScreen::UpdateGameLobbyDrawFrame() - Received notification [ {} ]", ss.str());

            switch(gn.getType())
            {
                case NotificationType::JOIN:
                {
                    auto newPlayer = std::make_shared<Player>( gn.getName(), gn.getUuid(), 2 );
                    mPlayerManager.AddPlayerToGame(gn.getUuid(), newPlayer);
                    break;
                }
                case NotificationType::LEAVE:
                {
                    mPlayerManager.RemovePlayerFromGame(gn.getUuid());
                    break;
                }
                case NotificationType::MESSAGE:
                {
                    mMessageProcessor.ProcessMessage(gn.getData());
                    break;
                }
                default:
                {
                    spdlog::get("console")->warn("GameLobbyScreen::UpdateGameLobbyDrawFrame() - Unknown notification [ {} ]");
                    break;
                }
            }
        }
        else
        {
            spdlog::get("stderr")->warn("GameLobbyScreen::UpdateGameLobbyDrawFrame() - Unknown notification [ {} ]");
        }
    }
}

// Update and Draw (one frame)
void GameLobbyScreen::UpdateGameLobbyDrawFrame(void)
{
    while (!WindowShouldClose() && !mReadyToStart)    // Detect window close button or ESC key
    {
        CheckForNotification();
        UpdateGameLobbyScreen();
        DrawGameLobbyScreen();
    }
}

void GameLobbyScreen::Show()
{
    SetTargetFPS(30);

    UpdateGameLobbyDrawFrame();

    CloseWindow();

    return;
}

