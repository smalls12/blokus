#define BOARD_SQUARE_SIZE       20
#define PIECE_SQUARE_SIZE       10

#define GRID_HORIZONTAL_SIZE    20
#define GRID_VERTICAL_SIZE      20

#include "OverlayBoard.hpp"

#include "ClearBoard.hpp"
#include "CheckBoundaries.hpp"
#include "AddPiece.hpp"

#include "PieceRotationIterator.hpp"

#include "spdlog/spdlog.h"

namespace
{
    static const int screenWidth = 600;
    static const int screenHeight = 600;
}

OverlayBoard::OverlayBoard()
:   mSelectedPiece(),
    mSelectedPieceLocation( Point(8, 8) ),
    mSelectedPieceRotation(0),
    mSelectedPieceMirrored(false)
{
    // spdlog::get("console")->info("OverlayBoard::OverlayBoard() - Start");
}

OverlayBoard::~OverlayBoard()
{
    // spdlog::get("console")->info("OverlayBoard::~OverlayBoard() - Start");
}

void OverlayBoard::SetSelectedGamePiece(Piece piece)
{
    std::stringstream ss;
    ss << piece;
    spdlog::get("console")->info("OverlayBoard::SetSelectedGamePiece() - Setting selected piece {}", ss.str());

    ClearBoard::EmptyBoard( *this );
    mSelectedPiece = piece;
    mSelectedPieceLocation = Point( 8, 8 );
    AddPiece::AddPieceToBoard( *this, mSelectedPiece, mSelectedPieceLocation );
}

Point OverlayBoard::MovePiece(MovementDirection direction)
{
    spdlog::get("console")->info("OverlayBoard::MoveSelectedPiece() - Start");

    ClearBoard::EmptyBoard( *this );

    switch(direction)
    {
        case MovementDirection::LEFT:
        {
            if ( CheckBoundaries::CheckLeftBoundary( mSelectedPieceLocation, mSelectedPiece.GetPadding() ) )
            {
                unsigned int moveLeft = mSelectedPieceLocation.GetY();
                mSelectedPieceLocation = Point( mSelectedPieceLocation.GetX(), --moveLeft );
            }
            else
            {
                spdlog::get("console")->error("OverlayBoard::MoveSelectedPiece() - Invalid, Left Border");
            }

            break;
        }
        case MovementDirection::RIGHT:
        {
            if ( CheckBoundaries::CheckRightBoundary( mSelectedPieceLocation, mSelectedPiece.GetPadding() ) )
            {
                unsigned int moveRight = mSelectedPieceLocation.GetY();
                mSelectedPieceLocation = Point( mSelectedPieceLocation.GetX(), ++moveRight );
            }
            else
            {
                spdlog::get("console")->error("OverlayBoard::MoveSelectedPiece() - Invalid, Right Border");
            }

            break;
        }
        case MovementDirection::UP:
        {
            if ( CheckBoundaries::CheckTopBoundary( mSelectedPieceLocation, mSelectedPiece.GetPadding() ) )
            {
                unsigned int moveUp = mSelectedPieceLocation.GetX();
                mSelectedPieceLocation = Point( --moveUp, mSelectedPieceLocation.GetY() );
            }
            else
            {
                spdlog::get("console")->error("OverlayBoard::MoveSelectedPiece() - Invalid, Top Border");
            }

            break;
        }
        case MovementDirection::DOWN:
        {
            if ( CheckBoundaries::CheckBottomBoundary( mSelectedPieceLocation, mSelectedPiece.GetPadding() ) )
            {
                unsigned int moveDown = mSelectedPieceLocation.GetX();
                mSelectedPieceLocation = Point( ++moveDown, mSelectedPieceLocation.GetY() );
            }
            else
            {
                spdlog::get("console")->error("OverlayBoard::MoveSelectedPiece() - Invalid, Bottom Border");
            }

            break;
        }
        default:
        {
            spdlog::get("console")->error("OverlayBoard::MoveSelectedPiece() - Invalid direction");
            break;
        }
    }

    AddPiece::AddPieceToBoard( *this, mSelectedPiece, mSelectedPieceLocation );

    return mSelectedPieceLocation;
}

void OverlayBoard::RotatePiece()
{
    spdlog::get("console")->info("OverlayBoard::RotatePiece() - Start");

    if( mSelectedPieceRotation >= PieceRotationIterator::GetIterator().size() - 1 )
    {
        mSelectedPieceRotation = 0;
    }
    else
    {
        mSelectedPieceRotation++;
    }
}

void OverlayBoard::MirrorPiece()
{
    spdlog::get("console")->info("OverlayBoard::MirrorPiece() - Start");
}

void OverlayBoard::FlipPiece()
{
    spdlog::get("console")->info("OverlayBoard::FlipPiece() - Start");
}