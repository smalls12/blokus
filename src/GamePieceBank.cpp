#include "GamePieceBank.hpp"

#include "BuildGamePieces.hpp"

GamePieceBank::GamePieceBank()
{
    mGamePieces = std::map<PlayerColor, std::map<PieceType, MoveablePiece>> {
        { PlayerColor::BLUE, BuildGamePieces::Build(GridSquare::PLAYER_ONE) },
        { PlayerColor::RED, BuildGamePieces::Build(GridSquare::PLAYER_TWO) },
        { PlayerColor::YELLOW, BuildGamePieces::Build(GridSquare::PLAYER_THREE) },
        { PlayerColor::GREEN, BuildGamePieces::Build(GridSquare::PLAYER_FOUR) },
    };
}

GamePieceBank::~GamePieceBank()
{

}

MoveablePiece* GamePieceBank::GetPlayerPiece(const PlayerColor color, const PieceType type)
{
    return &mGamePieces.at(color).at(type);
}
