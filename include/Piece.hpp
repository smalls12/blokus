#pragma once

#include "Point.hpp"
#include "Padding.hpp"
#include "Layout.hpp"
#include "PieceType.hpp"

class Piece
{
    public:
        Piece();
        ~Piece();
        Piece(Point offset, Padding padding, Layout layout, PieceType type);

        void SetOffset(Point offset) { mOffset = offset; }
        Point GetOffset() { return mOffset; }
    
        void SetPadding(Padding padding) { mPadding = padding; }
        Padding GetPadding() { return mPadding; }

        void SetLayout(Layout layout) { mLayout = layout ;}
        Layout GetLayout() { return mLayout; }

        void SetType(PieceType type) { mType = type; }
        PieceType GetType() {return mType; }

    private:
        // represent the offset from (0, 0) to draw on the screen
        Point       mOffset;
        // represents the available space inside the layout
        Padding     mPadding;
        Layout      mLayout;
        PieceType   mType;
};