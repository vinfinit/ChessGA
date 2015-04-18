#ifndef KNIGHT_H
#define KNIGHT_H

#include "chesspiece.h"

class Knight : public ChessPiece
{
public:
    Knight(Move curPos, Color color) : ChessPiece(ChessType::Knight, curPos, color) {}
    ~Knight();

    MoveList permissibleMove() override;
};

#endif // KNIGHT_H
