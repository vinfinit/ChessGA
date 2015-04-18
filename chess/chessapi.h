#ifndef CHESSAPI_H
#define CHESSAPI_H

#include <vector>

#include "king.h"
#include "pawn.h"
#include "bishop.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"

typedef std::vector<ChessPiece*> ChessList;

class ChessAPI
{
private:
    ChessList listWhiteChess;
    ChessList listBlackChess;

    Color next;

    ChessList init(Color color);
    MoveList mutableMove(ChessPiece* chess);
public:
    ChessAPI();
    ~ChessAPI();

    ChessList getWhiteChess() { return listWhiteChess; }
    ChessList getBlackChess() { return listBlackChess; }

    MoveList getMove(Move from);
};

#endif // CHESSAPI_H
