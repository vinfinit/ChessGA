#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook : public ChessPiece
{
public:
    Rook(Move curPos, Color color) : ChessPiece(ChessType::Rook, curPos, color) {}
    ~Rook();

    MoveList permissibleMove() override;
    MoveList getBlockMove(Move blockMove, MoveList curMoveList) override;
    MoveList getAttackMove(MoveList curMoveList) override;
};

#endif // ROOK_H
