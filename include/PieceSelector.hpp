#pragma once

/* =========================================================
 *
 * PieceSelector.hpp
 * 
 * Used by the game board to move the cursor used to select game
 * pieces to play
 * 
 * ========================================================= */

#include "PieceType.hpp"

class PieceSelector
{
    public:
        PieceSelector();
        ~PieceSelector();

        PieceType GetNextPiece();

    private:
        // private methods
        void IncrementIndex();

        // private variables
        unsigned int        mIndex;

};