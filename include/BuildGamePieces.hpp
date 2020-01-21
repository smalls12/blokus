#pragma once

/* =========================================================
 *
 * BuildGamePieces.hpp
 * 
 * Used to populate a map of game pieces
 * Each player gets the same set of pieces
 * This object will build these pieces and return a map thats indexed by the type of piece
 * 
 * ========================================================= */

#include "PieceType.hpp"
#include "Piece.hpp"

#include <map>

class BuildGamePieces
{
    public:
        // a map of pieces
        //  key is the type of piece
        //  value is piece itself
        static std::map<PieceType, Piece> Build(GridSquare gridSquare);

    private:
        BuildGamePieces();
        ~BuildGamePieces();
};