#include "PiecesAvailableForPlayLocations.hpp"

PiecesAvailableForPlayLocations::PiecesAvailableForPlayLocations()
{
    mLocations = std::map<PieceType, const Point> {
        { PieceType::I5, Point( 525, 125 ) }, // I1
        { PieceType::N, Point( 525, 325 ) }, // I2
        { PieceType::V5, Point( 525, 425 ) }, // V3
        { PieceType::T5, Point( 525, 525 ) }, // I3
        { PieceType::U, Point( 325, 25 ) }, // O
        { PieceType::L5, Point( 425, 525 ) }, // T4
        { PieceType::Y, Point( 525, 125 ) }, // I4
        { PieceType::Z5, Point( 525, 225 ) }, // L4
        { PieceType::W, Point( 425, 25 ) }, // Z4
        { PieceType::P, Point( 525, 25 ) }, // L5
        { PieceType::X, Point( 125, 25 ) }, // T5
        { PieceType::Z4, Point( 325, 525 ) }, // V5
        { PieceType::I4, Point( 125, 525 ) }, // N
        { PieceType::L4, Point( 225, 525 ) }, // Z5
        { PieceType::O, Point( 25, 425 ) }, // I5
        { PieceType::T4, Point( 25, 525 ) }, // P
        { PieceType::I3, Point( 25, 325 ) }, // W
        { PieceType::V3, Point( 25, 225 ) }, // U
        { PieceType::I2, Point( 25, 125 ) }, // F
        { PieceType::I1, Point( 25, 25 ) }, // X
        { PieceType::F, Point( 225, 25 ) }
    };
}

PiecesAvailableForPlayLocations::~PiecesAvailableForPlayLocations()
{

}

Point PiecesAvailableForPlayLocations::GetPieceLocation(PieceType type)
{
    return mLocations.at(type);
}
