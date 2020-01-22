#pragma once

#include "Board.hpp"
#include "MoveablePiece.hpp"
#include "Point.hpp"

class ValidateMove
{
    public:
        // NOTE
        // Might only need layout instead of Piece
        inline static bool ValidatePlayerMove(Board board, MoveablePiece& piece, Point point)
        {
            // see if any squares are already taken
            for (int i = 0; i < 5; i++)
            {
                for (int j = 0; j < 5; j++)
                {
                    // if the piece has a non empty square
                    // check to see if that spot on the board is available
                    if ( piece.GetLayout().Get(i, j) != GridSquare::EMPTY )
                    {
                        if ( board.Get( Point( point.GetX() + i, point.GetY() + j ) ) != GridSquare::EMPTY )
                        {
                            // spot already taken
                            return false;
                        }
                    }
                }
            }

            return true;
        }
};