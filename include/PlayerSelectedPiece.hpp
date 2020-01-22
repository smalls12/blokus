#pragma once

/* =========================================================
 *
 * PlayerSelectedPiece.hpp
 * 
 * Storing a raw pointer
 * The object does not own the pointer
 * 
 * ========================================================= */

#include "MoveablePiece.hpp"

class PlayerSelectedPiece
{
    public:
        PlayerSelectedPiece(MoveablePiece* moveablePiece);
        ~PlayerSelectedPiece();

        MoveablePiece* GetPiece() { return mMoveablePiece; }

        PlayerSelectedPiece& operator=(const PlayerSelectedPiece& other)
        {
            mMoveablePiece = other.mMoveablePiece;
            return *this;
        }

    private:
        // private variables
        MoveablePiece*      mMoveablePiece;

};