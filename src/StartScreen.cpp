extern "C" {
#include "raylib.h"
#include "raygui.h"
}

#include "StartScreen.hpp"
#include "GameMode.hpp"

#include "spdlog/spdlog.h"

#include <sstream>
#include <vector>
#include <iostream>

#define MAX_INPUT_CHARS     9

static const int screenWidth = 800;
static const int screenHeight = 450;

static bool GameModeSelectionMade = false;

char username[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for line ending char '\0'
int usernameLetterCount = 0;

char gameName[MAX_INPUT_CHARS + 1] = "\0";      // NOTE: One extra space required for line ending char '\0'
int gameNameLetterCount = 0;

enum InputSelection
{
    USERNAME = 0,
    GAMENAME
};

InputSelection currentInputSelection = USERNAME;

Rectangle usernameTextBox = { 100, 180, 225, 50 };
Rectangle gameNameTextBox = { 100, 300, 225, 50 };

Rectangle JoinGameBackground = { screenWidth / 2, 0, screenWidth, screenHeight };

int ListView000ScrollIndex = 0;
int ListView000Active = 0;

bool Button000Pressed = false;

bool mouseOnText = false;

int framesCounter = 0;

StartScreen::StartScreen(FindGame& findGame, ActiveGameManager& activeGameManager)
:   mFindGame(findGame),
    mActiveGameManager(activeGameManager),
    mGame()
{
    spdlog::get("console")->info("StartScreen::StartScreen() - Start");
}

StartScreen::~StartScreen()
{
    spdlog::get("console")->info("StartScreen::~StartScreen() - Start");
}

void StartScreen::UpdateStartScreen()
{
    if (Button000Pressed)
    {
        if (usernameLetterCount > 0)
        {
            std::vector<std::shared_ptr<ActiveGame>> listOfActiveGames = mActiveGameManager.GetListOfActiveGames();
            mGame.SetGameMode(GameMode::JOIN);
            mGame.SetGameConfiguration(GameConfiguration::TWO_PLAYER);
            mGame.SetUsername(std::string(username));
            mGame.SetGameName(listOfActiveGames[ListView000ScrollIndex]->GetGameName());
            mGame.SetServer(listOfActiveGames[ListView000ScrollIndex]->GetServer());
            GameModeSelectionMade = true;
        }
        else
        {
            spdlog::get("stderr")->error("StartScreen::StartScreen() - Use valid username.");
        }
    }

    if( !GameModeSelectionMade )
    {
        if (IsKeyPressed(KEY_TAB))
        {
            switch( currentInputSelection )
            {
                case USERNAME:
                {
                    currentInputSelection = GAMENAME;
                    break;
                }
                case GAMENAME:
                {
                    currentInputSelection = USERNAME;
                    break;
                }
                default:
                {
                    currentInputSelection = USERNAME;
                    break;
                }
            }
        }

        if (IsKeyPressed(KEY_BACKSPACE))
        {
            switch( currentInputSelection )
            {
                case USERNAME:
                {
                    usernameLetterCount--;
                    username[usernameLetterCount] = '\0';

                    if (usernameLetterCount < 0)
                    {
                        usernameLetterCount = 0;
                    }
                    break;
                }
                case GAMENAME:
                {
                    gameNameLetterCount--;
                    gameName[gameNameLetterCount] = '\0';

                    if (gameNameLetterCount < 0)
                    {
                        gameNameLetterCount = 0;
                    }
                    break;
                }
                default:
                {
                    currentInputSelection = USERNAME;
                    break;
                }
            }
        }

        if (IsKeyPressed(KEY_ENTER))
        {
            if (usernameLetterCount > 0 && gameNameLetterCount > 0)
            {
                mGame.SetGameMode(GameMode::START);
                mGame.SetGameConfiguration(GameConfiguration::TWO_PLAYER);
                mGame.SetUsername(std::string(username));
                mGame.SetGameName(std::string(gameName));
                mGame.SetServer(std::string(""));
                GameModeSelectionMade = true;
            }
            else
            {
                spdlog::get("stderr")->error("StartScreen::StartScreen() - Use valid username and game name.");
            }
        }

        // Get pressed key (character) on the queue
        int key = GetKeyPressed();

        // Check if more characters have been pressed on the same frame
        while (key > 0)
        {
            switch( currentInputSelection )
            {
                case USERNAME:
                {
                    // NOTE: Only allow keys in range [32..125]
                    if ((key >= 32) && (key <= 125) && (usernameLetterCount < MAX_INPUT_CHARS))
                    {
                        username[usernameLetterCount] = (char)key;
                        usernameLetterCount++;
                    }
                    break;
                }
                case GAMENAME:
                {
                    // NOTE: Only allow keys in range [32..125]
                    if ((key >= 32) && (key <= 125) && (gameNameLetterCount < MAX_INPUT_CHARS))
                    {
                        gameName[gameNameLetterCount] = (char)key;
                        gameNameLetterCount++;
                    }
                    break;
                }
                default:
                {
                    currentInputSelection = USERNAME;
                    break;
                }
            }
            
            key = GetKeyPressed();  // Check next character in the queue
        }

        framesCounter++;
    }
}

void StartScreen::DrawActiveGames()
{
    // Note
    //
    // This seems pretty expensive
    // Every time the screen renders, this map is cleared and rebuilt
    std::stringstream ss;
    std::vector<std::shared_ptr<ActiveGame>> listOfActiveGames = mActiveGameManager.GetListOfActiveGames();
    for( auto g : listOfActiveGames )
    {
        ss << g->GetGameName();
        ss << ";";
    }

    ListView000Active = GuiListView((Rectangle){ screenWidth / 2 + 100, 120, 240, 200 }, ss.str().c_str(), &ListView000ScrollIndex, ListView000Active);
    Button000Pressed = GuiButton((Rectangle){ screenWidth / 2 + 100, screenHeight - 100, 125, 30 }, "JOIN GAME"); 
}

void StartScreen::DrawUserName()
{
    DrawText("Username", 100, 140, 20, RED);

    DrawRectangleRec(usernameTextBox, LIGHTGRAY);
    Rectangle border = { usernameTextBox.x, usernameTextBox.y, usernameTextBox.width, usernameTextBox.height };
    int thickness = 1;
    if(currentInputSelection == USERNAME)
    {
        thickness++;
    }
    DrawRectangleLinesEx(border, thickness, RED);
    
    DrawText(username, usernameTextBox.x + 5, usernameTextBox.y + 8, 40, MAROON);
}

void StartScreen::DrawGameName()
{
    DrawText("Game Name", 100, 270, 20, RED);

    DrawRectangleRec(gameNameTextBox, LIGHTGRAY);
    Rectangle border = { gameNameTextBox.x, gameNameTextBox.y, gameNameTextBox.width, gameNameTextBox.height };
    int thickness = 1;
    if(currentInputSelection == GAMENAME)
    {
        thickness++;
    }
    DrawRectangleLinesEx(border, thickness, RED);

    DrawText(gameName, gameNameTextBox.x + 5, gameNameTextBox.y + 8, 40, MAROON);
}

void StartScreen::DrawBlinkingUnderscore()
{
    switch( currentInputSelection )
    {
        case USERNAME:
        {
            if (usernameLetterCount < MAX_INPUT_CHARS)
            {
                // Draw blinking underscore char
                if (((framesCounter/5)%2) == 0)
                {
                    DrawText("_", usernameTextBox.x + 8 + MeasureText(username, 40), usernameTextBox.y + 12, 40, MAROON);
                }
            }
            break;
        }
        case GAMENAME:
        {
            if (gameNameLetterCount < MAX_INPUT_CHARS)
            {
                // Draw blinking underscore char
                if (((framesCounter/5)%2) == 0)
                {
                    DrawText("_", gameNameTextBox.x + 8 + MeasureText(gameName, 40), gameNameTextBox.y + 12, 40, MAROON);
                }
            }
            break;
        }
        default:
        {
            currentInputSelection = USERNAME;
            break;
        }
    }
}

void StartScreen::DrawStartScreen()
{
    BeginDrawing();

    ClearBackground(RAYWHITE);

    DrawRectangleRec(JoinGameBackground, DARKGRAY);

    DrawText("Start Game", 80, 60, 30, GRAY);
    DrawText("Join Game", screenWidth / 2 + 80, 60, 30, BLACK);

    DrawUserName();

    DrawGameName();

    DrawBlinkingUnderscore();

    DrawActiveGames();
    
    EndDrawing();
}

// Update and Draw (one frame)
void StartScreen::UpdateStartScreenDrawFrame(void)
{
    while (!WindowShouldClose() && !GameModeSelectionMade)    // Detect window close button or ESC key
    {
        mFindGame();
        UpdateStartScreen();
        DrawStartScreen();
    }
}

Game StartScreen::Show()
{
    SetTargetFPS(30);

    UpdateStartScreenDrawFrame();

    return mGame;
}

