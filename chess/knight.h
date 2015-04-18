#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class Knight : ChessPiece
{
public:
    Knight(Move curPos, Color color) : ChessPiece(curPos, color) {}
    ~Knight();

    MoveList permissibleMove() override;
};

#endif // KNIGHT_H
