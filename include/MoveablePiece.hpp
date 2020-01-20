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

        MoveablePiece(const MoveablePiece &other) : Piece(other) {}
        MoveablePiece& operator=(MoveablePiece other)
        {
            // check for self-assignment
            if(&other == this)
                return *this;
            
            std::swap(mLayout, other.mLayout);
            std::swap(mPadding, other.mPadding);
            std::swap(mLocation, other.mLocation);

            return *this;
        }
    
        void SetLocation(Point location) { mLocation = location; }
        Point GetLocation() { return mLocation; }

        friend std::ostream& operator <<(std::ostream& outputStream, const MoveablePiece& p);

    private:
        // represent the offset from (0, 0) to draw on the screen
        Point       mLocation;
};