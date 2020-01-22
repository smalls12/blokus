#pragma once

/* =========================================================
 *
 * MoveablePiece.hpp
 * 
 * Extends base piece class
 * 
 * Contains a location on the board
 * 
 * ========================================================= */

#include "Piece.hpp"
#include "Point.hpp"

#include <ostream>

class MoveablePiece : public Piece
{
    public:
        MoveablePiece(Piece piece);
        MoveablePiece(Layout layout, Padding padding);
        ~MoveablePiece();
    
        void SetLocation(Point location) { mLocation = location; }
        Point GetLocation() { return mLocation; }

        void PiecePlayed() { mPlayed = true; }
        bool HasPieceBeenPlayed() { return mPlayed; }

        friend std::ostream& operator <<(std::ostream& outputStream, const MoveablePiece& p);

    private:
        // represent the offset from (0, 0) to draw on the screen
        Point       mLocation;
        bool        mPlayed;
};