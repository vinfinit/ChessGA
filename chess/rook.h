#ifndef ROOK_H
#define ROOK_H

#include "chesspiece.h"

class Rook : public ChessPiece
{
public:
    Rook(Move curPos, Color color) : ChessPiece(curPos, color) {}
    ~Rook();

    MoveList permissibleMove() override;
};

#endif // ROOK_H
