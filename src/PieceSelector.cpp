#include "PieceSelector.hpp"

#include "PieceTypeIterator.hpp"

PieceSelector::PieceSelector()
:   mIndex(0)
{

}

PieceSelector::~PieceSelector()
{

}

PieceType PieceSelector::GetNextPiece()
{
    unsigned int currentIndex = mIndex;
    IncrementIndex();
    return PieceTypeIterator::GetIterator()[currentIndex];
}

void PieceSelector::IncrementIndex()
{
    if( mIndex >= PieceTypeIterator::GetIterator().size() - 1 )
    {
        mIndex = 0;
    }
    else
    {
        mIndex++;
    }
}