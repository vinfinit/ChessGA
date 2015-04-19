#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

class Queen : public ChessPiece
{
public:
    Queen(Move curPos, Color color) : ChessPiece(ChessType::Queen, curPos, color) {}
    ~Queen();

    MoveList permissibleMove() override;
    MoveList getBlockMove(Move blockMove, MoveList curMoveList) override;
    MoveList getAttackMove(MoveList curMoveList) override;
};

#endif // QUEEN_H
