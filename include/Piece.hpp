#pragma once

/* =========================================================
 *
 * Piece.hpp
 * 
 * Base class, all pieces need this information
 * 
 * Used to draw a game piece
 * 
 * The layout of the piece is provided externally and tracked
 * The padding is calculated based on the layout and grid size
 * 
 * ========================================================= */

#include "Padding.hpp"
#include "Layout.hpp"

class Piece
{
    public:
        Piece();
        Piece(Layout layout);
        Piece(Layout layout, Padding padding);
        ~Piece();
    
        void SetLayout(Layout layout) { mLayout = layout ;}
        Layout GetLayout() { return mLayout; }

        void SetPadding(Padding padding) { mPadding = padding; }
        Padding GetPadding() { return mPadding; }

        friend std::ostream& operator <<(std::ostream& outputStream, const Piece& p);

    protected:
        // represents the available space inside the layout
        Layout      mLayout;
        Padding     mPadding;
        
    private:

};