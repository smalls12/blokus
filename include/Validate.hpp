#pragma once

/* =========================================================
 *
 * Validate.hpp
 * 
 * This class is used to validate the proposed piece location of the user
 * 
 * The validation will employ several for loops to iterate over each
 * grid square one by one
 * 
 * The game boards themselves are only 20x20 ( 400 loop iterations ), so
 * this will not be CPU intensive or take too long to perform
 * 
 * Two different modes of validation
 * 1. Initial move
 * 2. Normal gameplay ( after initial move )
 * 
 * ========================================================= */

#include "Board.hpp"
#include "MoveablePiece.hpp"
#include "Point.hpp"

class Validate
{
    public:
        // the first move of the game validates a piece being played in the corner
        inline static bool InitialMove(Board& base, Board& overlay)
        {
            // just confirm that the piece played is in one of the four corners
            bool valid = true;

            // top left corner
            if (    overlay.Get( Point(1, 1) ) != GridSquare::EMPTY ||
                    overlay.Get( Point(1, 18) ) != GridSquare::EMPTY ||
                    overlay.Get( Point(18, 1) ) != GridSquare::EMPTY ||
                    overlay.Get( Point(18, 18) ) != GridSquare::EMPTY )
            {
                // check for piecs on top of each other
                for (int i = 1; i < 19; i++)
                {
                    for (int j = 1; j < 19; j++)
                    {
                        // found a square containing a piece attempting to be played
                        if ( overlay.Get( Point(i, j) ) != GridSquare::EMPTY )
                        {
                            /* =========================================================
                            * Pieces ontop of other Pieces
                            * ========================================================= */

                            // see if the base is already occupied at that location
                            if ( base.Get( Point(i, j) ) != GridSquare::EMPTY )
                            {
                                // set the location on the overlay to draw custom square indicating the invalid
                                // piece location
                                overlay.Set( Point(i, j), GridSquare::INVALID );
                                valid = false;

                                // we found a reason for this move to be invalid
                                // move on to next square
                                continue;
                            }
                        }
                    }
                }
            }
            else
            {
                for (int i = 1; i < 19; i++)
                {
                    for (int j = 1; j < 19; j++)
                    {
                        // found a square containing a piece attempting to be played
                        if ( overlay.Get( Point(i, j) ) != GridSquare::EMPTY )
                        {
                            // set the location on the overlay to draw custom square indicating the invalid
                            // piece location
                            overlay.Set( Point(i, j), GridSquare::INVALID );
                            valid = false;
                        }
                    }
                }
            }

            return valid;
        }

        // validates an entire board at once
        inline static bool Normal(Board& base, Board& overlay)
        {
            bool valid = true;

            for (int i = 1; i < 19; i++)
            {
                for (int j = 1; j < 19; j++)
                {
                    // found a square containing a piece attempting to be played
                    if ( overlay.Get( Point(i, j) ) != GridSquare::EMPTY )
                    {
                        /* =========================================================
                         * Pieces ontop of other Pieces
                         * ========================================================= */

                        // see if the base is already occupied at that location
                        if ( base.Get( Point(i, j) ) != GridSquare::EMPTY )
                        {
                            // set the location on the overlay to draw custom square indicating the invalid
                            // piece location
                            overlay.Set( Point(i, j), GridSquare::INVALID );
                            valid = false;

                            // we found a reason for this move to be invalid
                            // move on to next square
                            continue;
                        }

                        /* =========================================================
                         * Invalid to have pieces of the same color directly adjacent
                         * ========================================================= */

                        // also need to check adjacencies
                        // search for pieces of the same color invalidating the game conditions
                        // ie. pieces of the same color can only be played on the corners
                        int TOP_BOUNDARY = i - 1;
                        if ( base.Get( Point(TOP_BOUNDARY, j) ) == overlay.Get( Point(i, j) ) )
                        {
                            // set the location on the overlay to draw custom square indicating the invalid
                            // piece location
                            overlay.Set( Point(i, j), GridSquare::INVALID );
                            valid = false;

                            // we found a reason for this move to be invalid
                            // move on to next square
                            continue;
                        }

                        int BOTTOM_BOUNDARY = i + 1;
                        if ( base.Get( Point(BOTTOM_BOUNDARY, j) ) == overlay.Get( Point(i, j) ) )
                        {
                            // set the location on the overlay to draw custom square indicating the invalid
                            // piece location
                            overlay.Set( Point(i, j), GridSquare::INVALID );
                            valid = false;

                            // we found a reason for this move to be invalid
                            // move on to next square
                            continue;
                        }

                        int LEFT_BOUNDARY = j - 1;
                        if ( base.Get( Point(i, LEFT_BOUNDARY) ) == overlay.Get( Point(i, j) ) )
                        {
                            // set the location on the overlay to draw custom square indicating the invalid
                            // piece location
                            overlay.Set( Point(i, j), GridSquare::INVALID );
                            valid = false;

                            // we found a reason for this move to be invalid
                            // move on to next square
                            continue;
                        }

                        int RIGHT_BOUNDARY = j + 1;
                        if ( base.Get( Point(i, RIGHT_BOUNDARY) ) == overlay.Get( Point(i, j) ) )
                        {
                            // set the location on the overlay to draw custom square indicating the invalid
                            // piece location
                            overlay.Set( Point(i, j), GridSquare::INVALID );
                            valid = false;

                            // we found a reason for this move to be invalid
                            // move on to next square
                            continue;
                        }

                        /* =========================================================
                         * Pieces can only be played against the corners of already
                         * laid pieces of the same color
                         * ========================================================= */

                        if ( base.Get( Point(TOP_BOUNDARY, LEFT_BOUNDARY) ) == overlay.Get( Point(i, j) ) )
                        {
                            // we found a reason for this move to be valid
                            // move on to next square
                            continue;
                        }

                        if ( base.Get( Point(TOP_BOUNDARY, RIGHT_BOUNDARY) ) == overlay.Get( Point(i, j) ) )
                        {
                            // we found a reason for this move to be valid
                            // move on to next square
                            continue;
                        }

                        if ( base.Get( Point(BOTTOM_BOUNDARY, LEFT_BOUNDARY) ) == overlay.Get( Point(i, j) ) )
                        {
                            // we found a reason for this move to be valid
                            // move on to next square
                            continue;
                        }

                        if ( base.Get( Point(BOTTOM_BOUNDARY, RIGHT_BOUNDARY) ) == overlay.Get( Point(i, j) ) )
                        {
                            // we found a reason for this move to be valid
                            // move on to next square
                            continue;
                        }

                        // not a valid mvoe
                        // set the location on the overlay to draw custom square indicating the invalid
                        // piece location
                        overlay.Set( Point(i, j), GridSquare::INVALID );
                        valid = false;
                    }
                }
            }

            return valid;
        }
};