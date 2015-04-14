#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(Move curPos, Color color) : ChessPiece(curPos, color) {}
    ~Pawn();

    MoveList permissibleMove() override;
};

#endif // PAWN_H
