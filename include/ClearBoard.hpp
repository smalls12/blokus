#pragma once

#include "Board.hpp"

class ClearBoard
{
    public:
        // NOTE
        // Might only need layout instead of Piece
        inline static void EmptyBoard(Board& board)
        {
            for (int i = 0; i < 20; i++)
            {
                for (int j = 0; j < 20; j++)
                {
                    board.Set( Point(i, j), GridSquare::EMPTY );
                }
            }
        }
};