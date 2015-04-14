#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

class Queen : public ChessPiece
{
public:
    Queen(Move curPos, Color color) : ChessPiece(curPos, color) {}
    ~Queen();

    MoveList permissibleMove() override;
};

#endif // QUEEN_H
