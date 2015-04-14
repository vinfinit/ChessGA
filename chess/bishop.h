#ifndef BISHOP_H
#define BISHOP_H

#include "chesspiece.h"

class Bishop : public ChessPiece
{
public:
    Bishop(Move curPos, Color color) : ChessPiece(curPos, color) {}
    ~Bishop();

    MoveList permissibleMove() override;
};

#endif // BISHOP_H
