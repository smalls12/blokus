#pragma once

class GameScreen
{
    public:
        GameScreen();
        ~GameScreen();

        bool Show();

    private:
        void InitializeGamePieces();
        void InitGame();
        bool ProcessPlayerMove();
        void UpdateGame();
        void DrawBoard();
        void DrawGamePieces();
        void DrawOverlayBoard();
        void DrawSelector();
        void DrawGame();
        void UpdateDrawFrame();
        void UnloadGame();
};