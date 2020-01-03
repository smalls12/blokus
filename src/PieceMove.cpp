#include <PieceMove.hpp>

PieceMove::PieceMove(uint32_t piece, uint32_t x_pos, uint32_t y_pos)
{
    mPiece = piece,
    mXPos = x_pos;
    mYPos = y_pos;
}

PieceMove::~PieceMove()
{

}

uint32_t PieceMove::getPiece() const
{
    return mPiece;
}

uint32_t PieceMove::getXPos() const
{
    return mXPos;
}

uint32_t PieceMove::getYPos() const
{
    return mYPos;
}
