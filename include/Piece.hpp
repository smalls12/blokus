#pragma once

#include "Point.hpp"
#include "Padding.hpp"
#include "Layout.hpp"

class Piece
{
    public:
        Piece() = default;
        Piece(Point offset, Padding padding, Layout layout);

        Point GetOffset();
        Padding GetPadding();
        Layout GetLayout();

        void SetOffset(Point point);
        void SetPadding(Padding padding);
        void SetLayout(Layout layout);

    private:
        // represent the offset from (0, 0) to draw on the screen
        Point mOffset;
        // represents the available space inside the layout
        Padding mPadding;
        Layout mLayout;
};