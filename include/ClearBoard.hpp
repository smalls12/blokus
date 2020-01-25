#pragma once

#include "Board.hpp"

class ClearBoard
{
    public:
        // NOTE
        // Might only need layout instead of Piece
        inline static void EmptyBoard(Board& board)
        {
            // Initialize grid matrices
            for (int i = 0; i < GRID_HORIZONTAL_SIZE; i++)
            {
                for (int j = 0; j < GRID_VERTICAL_SIZE; j++)
                {
                    if ((j == GRID_VERTICAL_SIZE - 1) || (i == 0) || (i == GRID_HORIZONTAL_SIZE - 1) || (j == 0))
                    {
                        board.Set( Point(i, j), GridSquare::BLOCK );
                    }
                    else
                    {
                        board.Set( Point(i, j), GridSquare::EMPTY );
                    }
                }
            }

            
        }
};