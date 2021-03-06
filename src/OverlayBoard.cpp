#define BOARD_SQUARE_SIZE       20
#define PIECE_SQUARE_SIZE       10

#define GRID_HORIZONTAL_SIZE    20
#define GRID_VERTICAL_SIZE      20

#include "OverlayBoard.hpp"

#include "ClearBoard.hpp"
#include "CheckBoundaries.hpp"
#include "AddPiece.hpp"

#include "ManipulatePiece.hpp"
#include "PieceRotationIterator.hpp"

#include "spdlog/spdlog.h"

namespace
{
    static const int screenWidth = 600;
    static const int screenHeight = 600;
}

OverlayBoard::OverlayBoard()
:   mSelectedPiece(),
    mSelectedPieceRotation(0),
    mSelectedPieceFlipped(false),
    mSelectedPieceLocation( Point(8, 8) )
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
    mSelectedPieceRotation = 0;
    mSelectedPieceFlipped = false;
    mSelectedPieceLocation = Point( 8, 8 );
    AddPiece::AddPieceToBoard( *this, mSelectedPiece, mSelectedPieceLocation );
}

void OverlayBoard::MovePiece(MovementDirection direction)
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
}

void OverlayBoard::FlipPiece()
{
    spdlog::get("console")->info("OverlayBoard::FlipPiece() - Start");

    ClearBoard::EmptyBoard( *this );

    Layout temporaryLayout = mSelectedPiece.GetLayout();
    ManipulatePiece::Flip(temporaryLayout);
    mSelectedPiece = Piece(temporaryLayout);

    if (mSelectedPieceFlipped)
    {
        mSelectedPieceFlipped = false;
    }
    else
    {
        mSelectedPieceFlipped = true;
    }

    AddPiece::AddPieceToBoard( *this, mSelectedPiece, mSelectedPieceLocation );
}

void OverlayBoard::RotatePiece()
{
    spdlog::get("console")->info("OverlayBoard::RotatePiece() - Start");

    ClearBoard::EmptyBoard( *this );

    Layout temporaryLayout = mSelectedPiece.GetLayout();
    ManipulatePiece::Rotate(temporaryLayout);
    mSelectedPiece = Piece(temporaryLayout);

    if( mSelectedPieceRotation >= PieceRotationIterator::GetIterator().size() - 1 )
    {
        mSelectedPieceRotation = 0;
    }
    else
    {
        mSelectedPieceRotation++;
    }

    AddPiece::AddPieceToBoard( *this, mSelectedPiece, mSelectedPieceLocation );
}

void OverlayBoard::GetPieceData(IPlayerMoveRequestData& data)
{
    data.SetPieceRotation(PieceRotationIterator::GetIterator()[mSelectedPieceRotation]);
    data.SetPieceFlipped(mSelectedPieceFlipped);
    data.SetLocation(mSelectedPieceLocation);
}
