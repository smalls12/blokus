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
#include "MovementDirection.hpp"
#include "Piece.hpp"
#include "PieceRotation.hpp"

#include <vector>

class OverlayBoard : public Board
{
    public:
        OverlayBoard();
        ~OverlayBoard();

        void SetSelectedGamePiece(Piece piece);
        Point MovePiece(MovementDirection direction);
        void FlipPiece();
        void MirrorPiece();
        void RotatePiece();


    private:
        // this stores the piece that was selected by the user
        // untouched by the different manipulation options for the piece
        Piece           mSelectedPiece;

        // essentially a copy of the selected piece
        // used to manipulate the piece ( rotating, mirroring, flipping )
        // MoveablePiece   mDrawablePiece;

        Point           mSelectedPieceLocation;

        unsigned int    mSelectedPieceRotation;

        bool            mSelectedPieceMirrored;
};