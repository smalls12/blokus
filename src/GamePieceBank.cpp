#include "GamePieceBank.hpp"

#include "BuildGamePieces.hpp"

GamePieceBank::GamePieceBank()
{
    mGamePieces = std::map<PlayerId, std::map<PieceType, Piece>> {
        { PlayerId::PLAYER_ONE, BuildGamePieces::Build(PlayerColor::BLUE) },
        { PlayerId::PLAYER_TWO, BuildGamePieces::Build(PlayerColor::BLUE) },
        { PlayerId::PLAYER_THREE, BuildGamePieces::Build(PlayerColor::BLUE) },
        { PlayerId::PLAYER_FOUR, BuildGamePieces::Build(PlayerColor::BLUE) },
    };
}

GamePieceBank::~GamePieceBank()
{

}

Piece GamePieceBank::GetPlayerPiece(PlayerId id, PieceType type)
{
    return mGamePieces.at(id).at(type);
}
