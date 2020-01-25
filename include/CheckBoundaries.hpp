#pragma once

#include "Point.hpp"
#include "Padding.hpp"

class CheckBoundaries
{
    public:

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

        inline static bool CheckLeftBoundary(const Point& location, const Padding& padding)
        {
            if ( ( location.GetY() - 1 ) > ( 0 - padding.GetLeft() ) )
            {
                return true;
            }

            return false;
        }

        inline static bool CheckRightBoundary(const Point& location, const Padding& padding)
        {
            if ( ( location.GetY() + 1 ) < ( 15 + padding.GetRight() ) )
            {
                return true;
            }

            return false;
        }

        inline static bool CheckTopBoundary(const Point& location, const Padding& padding)
        {
            if ( ( location.GetX() - 1 ) > ( 0 - padding.GetTop() ) )
            {
                return true;
            }

            return false;
        }

        inline static bool CheckBottomBoundary(const Point& location, const Padding& padding)
        {
            if ( ( location.GetX() + 1 ) < ( 15 + padding.GetBottom() ) )
            {
                return true;
            }

            return false;
        }
};