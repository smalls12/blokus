#pragma once

#include "Board.hpp"
#include "Point.hpp"

class MergeBoards
{
    public:
        // take the pieces from the overlay and add to the base
        inline static bool Merge(Board& base, Board& overlay)
        {
            for (int i = 1; i < 19; i++)
            {
                for (int j = 1; j < 19; j++)
                {
                    switch( overlay.Get( Point(i, j) ) )
                    {
                        case GridSquare::EMPTY:
                        case GridSquare::BLOCK:
                        case GridSquare::INVALID:
                        {
                            break;
                        }
                        case GridSquare::PLAYER_ONE:
                        case GridSquare::PLAYER_TWO:
                        case GridSquare::PLAYER_THREE:
                        case GridSquare::PLAYER_FOUR:
                        {
                            base.Set( Point(i, j), overlay.Get( Point(i, j) ) );
                        }
                        default:
                        {
                            break;
                        }
                    }
                }
            }

            return true;
        }
};