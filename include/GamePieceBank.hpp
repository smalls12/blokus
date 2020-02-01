#pragma once

/* =========================================================
 *
 * GamePieceBank.hpp
 * 
 * Tracks game pieces for all players
 * 
 * ========================================================= */

#include "PlayerColor.hpp"
#include "PieceType.hpp"
#include "MoveablePiece.hpp"

#include <map>

class GamePieceBank
{
    public:
        GamePieceBank();
        ~GamePieceBank();

        // using a raw pointer here
        // a smart pointer would assume ownership
        // and remove the data once the reference counter hit 0
        // the smart pointer does not own this data
        MoveablePiece* GetPlayerPiece(const PlayerColor color, PieceType type);

    private:
        std::map<PlayerColor, std::map<PieceType, MoveablePiece>>   mGamePieces;
};