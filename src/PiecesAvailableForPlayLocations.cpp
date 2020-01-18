#include "PiecesAvailableForPlayLocations.hpp"

PiecesAvailableForPlayLocations::PiecesAvailableForPlayLocations()
{
    mLocations = std::map<PieceType, const Point> {
        { PieceType::I5, Point( 25, 25 ) },
        { PieceType::N, Point( 125, 25 ) },
        { PieceType::V5, Point( 225, 25 ) },
        { PieceType::T5, Point( 325, 25 ) },
        { PieceType::U, Point( 425, 25 ) },
        { PieceType::L5, Point( 525, 25 ) },
        { PieceType::Y, Point( 525, 125 ) },
        { PieceType::Z5, Point( 525, 225 ) },
        { PieceType::W, Point( 525, 325 ) },
        { PieceType::P, Point( 525, 425 ) },
        { PieceType::X, Point( 525, 525 ) },
        { PieceType::Z4, Point( 425, 525 ) },
        { PieceType::I4, Point( 325, 525 ) },
        { PieceType::L4, Point( 225, 525 ) },
        { PieceType::O, Point( 125, 525 ) },
        { PieceType::T4, Point( 25, 525 ) },
        { PieceType::I3, Point( 25, 425 ) },
        { PieceType::V3, Point( 25, 325 ) },
        { PieceType::I2, Point( 25, 225 ) },
        { PieceType::I1, Point( 25, 125 ) }
    };
}

PiecesAvailableForPlayLocations::~PiecesAvailableForPlayLocations()
{

}

Point PiecesAvailableForPlayLocations::GetPieceLocation(PieceType type)
{
    return mLocations.at(type);
}
