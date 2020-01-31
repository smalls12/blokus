#pragma once

/* =========================================================
 *
 * OverlayBoard.hpp
 * 
 * Extends base board class
 * 
 * This board contains a moveable piece
 * the piece can also be rotated/mirrored/flipped
 * ========================================================= */

#include "Board.hpp"
#include "Piece.hpp"
#include "MovementDirection.hpp"
#include "IPlayerMoveRequestData.hpp"
#include "PieceRotation.hpp"

#include <vector>

class OverlayBoard : public Board
{
    public:
        OverlayBoard();
        ~OverlayBoard();

        void SetSelectedGamePiece(Piece piece);
        void MovePiece(MovementDirection direction);
        void FlipPiece();
        void RotatePiece();
        void GetPieceData(IPlayerMoveRequestData& data);

    private:
        // this stores the piece that was selected by the user
        // untouched by the different manipulation options for the piece
        Piece           mSelectedPiece;

        // essentially a copy of the selected piece
        // used to manipulate the piece ( rotating, mirroring, flipping )
        // MoveablePiece   mDrawablePiece;

        unsigned int    mSelectedPieceRotation;

        bool            mSelectedPieceFlipped;

        Point           mSelectedPieceLocation;
};