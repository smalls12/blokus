#pragma once

#include <Piece.hpp>

#include <string>

class PieceMove
{
public:
    PieceMove(uint32_t piece, uint32_t x_pos, uint32_t y_pos);
    virtual ~PieceMove();

    uint32_t getPiece() const;
    uint32_t getXPos() const;
    uint32_t getYPos() const;

private:
    Piece *mSelectedPiece;

    uint32_t mPiece;
    uint32_t mXPos;
    uint32_t mYPos;
};