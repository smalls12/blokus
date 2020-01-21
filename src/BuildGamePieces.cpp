#include "BuildGamePieces.hpp"

#include "CalculatePadding.hpp"

std::map<PieceType, Piece> BuildGamePieces::Build(GridSquare gridSquare)
{
    Layout BlokusPiece1;
    BlokusPiece1.Set( Point(2, 2), gridSquare );

    Layout BlokusPiece2;
    BlokusPiece2.Set( Point(2, 2), gridSquare )
                .Set( Point(2, 3), gridSquare );

    Layout BlokusPiece3;
    BlokusPiece3.Set( Point(2, 2), gridSquare )
                .Set( Point(2, 3), gridSquare )
                .Set( Point(3, 3), gridSquare );

    Layout BlokusPiece4;
    BlokusPiece4.Set( Point(2, 1), gridSquare )
                .Set( Point(2, 2), gridSquare )
                .Set( Point(2, 3), gridSquare );

    Layout BlokusPiece5;
    BlokusPiece5.Set( Point(2, 1), gridSquare )
                .Set( Point(2, 2), gridSquare )
                .Set( Point(3, 1), gridSquare )
                .Set( Point(3, 2), gridSquare );

    Layout BlokusPiece6;
    BlokusPiece6.Set( Point(2, 2), gridSquare )
                .Set( Point(3, 1), gridSquare )
                .Set( Point(3, 2), gridSquare )
                .Set( Point(3, 3), gridSquare );

    Layout BlokusPiece7;
    BlokusPiece7.Set( Point(2, 1), gridSquare )
                .Set( Point(2, 2), gridSquare )
                .Set( Point(2, 3), gridSquare )
                .Set( Point(2, 4), gridSquare );

    Layout BlokusPiece8;
    BlokusPiece8.Set( Point(1, 3), gridSquare )
                .Set( Point(2, 1), gridSquare )
                .Set( Point(2, 2), gridSquare )
                .Set( Point(2, 3), gridSquare );

    Layout BlokusPiece9;
    BlokusPiece9.Set( Point(2, 2), gridSquare )
                .Set( Point(2, 3), gridSquare )
                .Set( Point(3, 1), gridSquare )
                .Set( Point(3, 2), gridSquare );

    Layout BlokusPiece10;
    BlokusPiece10.Set( Point(2, 4), gridSquare )
                 .Set( Point(3, 1), gridSquare )
                 .Set( Point(3, 2), gridSquare )
                 .Set( Point(3, 3), gridSquare )
                 .Set( Point(3, 4), gridSquare );

    Layout BlokusPiece11;
    BlokusPiece11.Set( Point(1, 2), gridSquare )
                 .Set( Point(2, 2), gridSquare )
                 .Set( Point(3, 1), gridSquare )
                 .Set( Point(3, 2), gridSquare )
                 .Set( Point(3, 3), gridSquare );

    Layout BlokusPiece12;
    BlokusPiece12.Set( Point(1, 1), gridSquare )
                 .Set( Point(2, 1), gridSquare )
                 .Set( Point(3, 1), gridSquare )
                 .Set( Point(3, 2), gridSquare )
                 .Set( Point(3, 3), gridSquare );

    Layout BlokusPiece13;
    BlokusPiece13.Set( Point(3, 1), gridSquare )
                 .Set( Point(3, 2), gridSquare )
                 .Set( Point(2, 2), gridSquare )
                 .Set( Point(2, 3), gridSquare )
                 .Set( Point(2, 4), gridSquare );

    Layout BlokusPiece14;
    BlokusPiece14.Set( Point(1, 3), gridSquare )
                 .Set( Point(2, 1), gridSquare )
                 .Set( Point(2, 2), gridSquare )
                 .Set( Point(2, 3), gridSquare )
                 .Set( Point(3, 1), gridSquare );

    Layout BlokusPiece15;
    BlokusPiece15.Set( Point(2, 0), gridSquare )
                 .Set( Point(2, 1), gridSquare )
                 .Set( Point(2, 2), gridSquare )
                 .Set( Point(2, 3), gridSquare )
                 .Set( Point(2, 4), gridSquare );

    Layout BlokusPiece16;
    BlokusPiece16.Set( Point(1, 1), gridSquare )
                 .Set( Point(2, 1), gridSquare )
                 .Set( Point(2, 2), gridSquare )
                 .Set( Point(3, 1), gridSquare )
                 .Set( Point(3, 2), gridSquare );

    Layout BlokusPiece17;
    BlokusPiece17.Set( Point(1, 3), gridSquare )
                 .Set( Point(1, 2), gridSquare )
                 .Set( Point(2, 2), gridSquare )
                 .Set( Point(2, 1), gridSquare )
                 .Set( Point(3, 1), gridSquare );

    Layout BlokusPiece18;
    BlokusPiece18.Set( Point(1, 2), gridSquare )
                 .Set( Point(1, 3), gridSquare )
                 .Set( Point(2, 2), gridSquare )
                 .Set( Point(3, 2), gridSquare )
                 .Set( Point(3, 3), gridSquare );

    Layout BlokusPiece19;
    BlokusPiece19.Set( Point(1, 2), gridSquare )
                 .Set( Point(1, 3), gridSquare )
                 .Set( Point(2, 1), gridSquare )
                 .Set( Point(2, 2), gridSquare )
                 .Set( Point(3, 2), gridSquare );

    Layout BlokusPiece20;
    BlokusPiece20.Set( Point(1, 2), gridSquare )
                 .Set( Point(2, 1), gridSquare )
                 .Set( Point(2, 2), gridSquare )
                 .Set( Point(2, 3), gridSquare )
                 .Set( Point(3, 2), gridSquare );

    Layout BlokusPiece21;
    BlokusPiece21.Set( Point(2, 2), gridSquare )
                 .Set( Point(3, 1), gridSquare )
                 .Set( Point(3, 2), gridSquare )
                 .Set( Point(3, 3), gridSquare )
                 .Set( Point(3, 4), gridSquare );

    std::map<PieceType, Piece> pieces = {
        { PieceType::I1, Piece( BlokusPiece1 ) },
        { PieceType::I2, Piece( BlokusPiece2 ) },
        { PieceType::V3, Piece( BlokusPiece3 ) },
        { PieceType::I3, Piece( BlokusPiece4 ) },
        { PieceType::O, Piece( BlokusPiece5 ) },
        { PieceType::T4, Piece( BlokusPiece6 ) },
        { PieceType::I4, Piece( BlokusPiece7 ) },
        { PieceType::L4, Piece( BlokusPiece8 ) },
        { PieceType::Z4, Piece( BlokusPiece9 ) },
        { PieceType::L5, Piece( BlokusPiece10 ) },
        { PieceType::T5, Piece( BlokusPiece11 ) },
        { PieceType::V5, Piece( BlokusPiece12 ) },
        { PieceType::N, Piece( BlokusPiece13 ) },
        { PieceType::Z5, Piece( BlokusPiece14 ) },
        { PieceType::I5, Piece( BlokusPiece15 ) },
        { PieceType::P, Piece( BlokusPiece16 ) },
        { PieceType::W, Piece( BlokusPiece17 ) },
        { PieceType::F, Piece( BlokusPiece18 ) },
        { PieceType::X, Piece( BlokusPiece19 ) },
        { PieceType::U, Piece( BlokusPiece20 ) },
        { PieceType::Y, Piece( BlokusPiece21 ) }
    };

    return pieces;
}