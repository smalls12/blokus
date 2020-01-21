#include "GamePieceBank.hpp"

#include "BuildGamePieces.hpp"

GamePieceBank::GamePieceBank()
{
    mGamePieces = std::map<PlayerId, std::map<PieceType, Piece>> {
        { PlayerId::PLAYER_ONE, BuildGamePieces::Build(GridSquare::PLAYER_ONE) },
        { PlayerId::PLAYER_TWO, BuildGamePieces::Build(GridSquare::PLAYER_TWO) },
        { PlayerId::PLAYER_THREE, BuildGamePieces::Build(GridSquare::PLAYER_THREE) },
        { PlayerId::PLAYER_FOUR, BuildGamePieces::Build(GridSquare::PLAYER_FOUR) },
    };
}

GamePieceBank::~GamePieceBank()
{

}

Piece GamePieceBank::GetPlayerPiece(PlayerId id, PieceType type)
{
    return mGamePieces.at(id).at(type);
}
