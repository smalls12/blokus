#pragma once

/* =========================================================
 *
 * PiecesAvailableForPlayLocations.hpp
 * 
 * Used by the game board to draw pieces that a user can select
 * to play during their move.
 * 
 * A piece will be mapped at a location on the gameboard.
 * 
 * This is just an encapsulated map
 * Allows access to begin and end functions for iteration to internal map
 * Allows access to key to obtain value
 * 
 * ========================================================= */

#include "PieceType.hpp"
#include "Piece.hpp"
#include "PlayerColor.hpp"

#include <map>

class PiecesAvailableForPlayLocations
{
    public:
        PiecesAvailableForPlayLocations();
        ~PiecesAvailableForPlayLocations();

        Point GetPieceLocation();

        std::map<PieceType, const Point>::const_iterator cbegin() { return mLocations.cbegin(); }
        std::map<PieceType, const Point>::const_iterator cend() { return mLocations.cend(); }

    private:
        std::map<PieceType, const Point>      mLocations;
};