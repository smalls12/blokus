#pragma once

#include "Board.hpp"
#include "MoveablePiece.hpp"
#include "Point.hpp"

class ValidateMove
{
    public:
        // validates an entire board at once
        inline static bool Validate(Board& base, Board& overlay)
        {
            for (int i = 1; i < 19; i++)
            {
                for (int j = 1; j < 19; j++)
                {
                    // found a square containing a piece attempting to be played
                    if ( overlay.Get( Point(i, j) ) != GridSquare::EMPTY )
                    {
                        // see if the base is already occupied at that location
                        if ( base.Get( Point(i, j) ) != GridSquare::EMPTY )
                        {
                            return false;
                        }

                        // also need to check adjacencies
                    }
                }
            }

            return true;
        }
};