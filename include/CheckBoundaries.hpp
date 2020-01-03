#pragma once

#include "Piece.hpp"
#include "Point.hpp"

#include "MovementDirection.hpp"

class CheckBoundaries
{
    public:
        // NOTE
        // Might only need layout instead of Piece
        inline static bool CheckGameBoardBoundary(Point CurrentLocation, Piece piece, MovementDirection direction)
        {
            // the calculation here is take the current location
            // ( x, y )
            //
            // add or subtract from the location based off of the direction
            // left         y - 1
            // right        y + 1
            // up           x - 1
            // down         x + 1
            //
            // the internal padding on the piece also needs to be considered

            switch(direction)
            {
                case MovementDirection::LEFT:
                {
                    if ( ( CurrentLocation.GetY() - 1 ) > ( 0 - piece.GetPadding().GetLeft() ) )
                    {
                        return true;
                    }
                    break;
                }
                case MovementDirection::RIGHT:
                {
                    if ( ( CurrentLocation.GetY() + 1 ) < ( 20 + piece.GetPadding().GetRight() ) )
                    {
                        return true;
                    }
                    break;
                }
                case MovementDirection::UP:
                {
                    if ( ( CurrentLocation.GetX() - 1 ) > ( 0 - piece.GetPadding().GetTop() ) )
                    {
                        return true;
                    }
                    break;
                }
                case MovementDirection::DOWN:
                {
                    if ( ( CurrentLocation.GetX() + 1 ) < ( 20 + piece.GetPadding().GetBottom() ) )
                    {
                        return true;
                    }
                    break;
                }
            }

            return false;
        }
};