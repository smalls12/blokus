#pragma once

/* =========================================================
 *
 * PlayerMoveRequestData.hpp
 * 
 * Concrete implementation for that data to build the
 * player move request
 * 
 * ========================================================= */

#include "IPlayerMoveRequestData.hpp"

class PlayerMoveRequestData : public IPlayerMoveRequestData
{
    public:
        PlayerMoveRequestData();
        ~PlayerMoveRequestData();

        void SetPlayerId(PlayerId id) { mPlayerId = id; }
        PlayerId GetPlayerId() { return mPlayerId; }

        void SetPieceType(PieceType type) { mPieceType = type; }
        PieceType GetPieceType() { return mPieceType; }

        void SetPieceRotation(PieceRotation rotation) { mPieceRotation = rotation; }
        PieceRotation GetPieceRotation() { return mPieceRotation; }

        void SetPieceFlipped(bool flipped) { mPieceFlipped = flipped; }
        bool GetPieceFlipped() { return mPieceFlipped; }

        void SetLocation(Point location) { mLocation = location; }
        Point GetLocation() { return mLocation; }

    private:
        PlayerId        mPlayerId;
        PieceType       mPieceType;
        PieceRotation   mPieceRotation;
        bool            mPieceFlipped;
        Point           mLocation;
};