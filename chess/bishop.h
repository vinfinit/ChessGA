#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(Move curPos, Color color) : ChessPiece(ChessType::Bishop, curPos, color) {}
    ~Bishop();

    MoveList permissibleMove() override;
    MoveList getBlockMove(Move blockMove, MoveList curMoveList) override;
    MoveList getAttackMove(MoveList curMoveList) override;
};

#endif // BISHOP_H
