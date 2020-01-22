#pragma once

#include "Board.hpp"
#include "MoveablePiece.hpp"
#include "Point.hpp"

#include "GridSquareString.hpp"

class AddPiece
{
    public:
        // NOTE
        // Might only need layout instead of Piece
        inline static void AddPieceToBoard(Board& board, MoveablePiece& piece, Point point)
        {
            // y-axis
            for (int i = 0; i < 5; i++)
            {
                // x-axis
                for (int j = 0; j < 5; j++)
                {
                    switch( piece.GetLayout().Get(i, j) )
                    {
                        case GridSquare::EMPTY:
                        case GridSquare::BLOCK:
                        {
                            break;
                        }
                        case GridSquare::PLAYER_ONE:
                        case GridSquare::PLAYER_TWO:
                        case GridSquare::PLAYER_THREE:
                        case GridSquare::PLAYER_FOUR:
                        {
                            board.Set( Point(point.GetX() + i, point.GetY() + j), piece.GetLayout().Get(i, j) );
                            break;
                        }
                        default:
                        {
                            break;
                        }
                    }
                }
            }
        }
};