#ifndef CHESSCONTROLLER_H
#define CHESSCONTROLLER_H

#include <vector>

#include "king.h"
#include "pawn.h"
#include "bishop.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"

typedef std::vector<ChessPiece*> ListChess;

class ChessController
{
private:
    ListChess listWhiteChess;
    ListChess listBlackChess;

    ListChess init(Color color);
public:
    ChessController();
    ~ChessController();

    ListChess getWhiteChess() { return listWhiteChess; }
    ListChess getBlackChess() { return listBlackChess; }
};

#endif // CHESSCONTROLLER_H
