#ifndef QUEEN_H
#define QUEEN_H

#include "chesspiece.h"

class Queen : public ChessPiece
{
public:
    Queen(Move curPos, Color color) : ChessPiece(ChessType::Queen, curPos, color) {}
    ~Queen();

    MoveList permissibleMove() override;
};

#endif // QUEEN_H
