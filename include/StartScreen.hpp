#pragma once

#include "FindGame.hpp"
#include "ActiveGameManager.hpp"
#include "Game.hpp"

class StartScreen
{
    public:
        StartScreen(FindGame& findGame, ActiveGameManager& activeGameManager);
        ~StartScreen();

        Game Show();

    private:
        void UpdateStartScreen();
        void DrawUserName();
        void DrawGameName();
        void DrawBlinkingUnderscore();
        void DrawActiveGames();
        void DrawStartScreen();
        void UpdateStartScreenDrawFrame();

        FindGame&                                           mFindGame;
        ActiveGameManager&                                  mActiveGameManager;

        Game                                                mGame;
};