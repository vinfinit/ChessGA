#ifndef PAWN_H
#define PAWN_H

#include "chesspiece.h"

class Pawn : public ChessPiece
{
public:
    Pawn(Move curPos, Color color) : ChessPiece(ChessType::Pawn, curPos, color) {}
    ~Pawn();

    MoveList permissibleMove() override;
    MoveList getAttackMove(MoveList) override;
};

#endif // PAWN_H
