#ifndef KING_H
#define KING_H

#include "chesspiece.h"

class King : public ChessPiece
{
public:
    King(Move curPos, Color color) : ChessPiece(ChessType::King, curPos, color) {}
    ~King();

    MoveList permissibleMove() override;
};

#endif // KING_H
