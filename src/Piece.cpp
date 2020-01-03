#include "Piece.hpp"

Piece::Piece(Point offset, Padding padding, Layout layout)
:   mOffset(offset),
    mPadding(padding),
    mLayout(layout)
{

}

Point Piece::GetOffset()
{
    return mOffset;
}

Padding Piece::GetPadding()
{
    return mPadding;
}

Layout Piece::GetLayout()
{
    return mLayout;
}

void Piece::SetOffset(Point point)
{
    mOffset = point;
}

void Piece::SetPadding(Padding padding)
{
    mPadding = padding;
}

void Piece::SetLayout(Layout layout)
{
    mLayout = layout;
}