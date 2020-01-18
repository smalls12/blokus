#pragma once

/* =========================================================
 *
 * GamePieceBank.hpp
 * 
 * Tracks game pieces for all players
 * 
 * ========================================================= */

#include "PlayerId.hpp"
#include "PieceType.hpp"
#include "Piece.hpp"

#include <map>

class GamePieceBank
{
    public:
        GamePieceBank();
        ~GamePieceBank();

        Piece GetPlayerPiece(PlayerId id, PieceType type);

    private:
        std::map<PlayerId, std::map<PieceType, Piece>>   mGamePieces;
};