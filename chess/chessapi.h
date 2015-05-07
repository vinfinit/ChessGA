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
    MoveList mutableAttack(ChessPiece* chess);

    bool removeChessPiece(Move pos);
    bool checkImprovePawn();
public:
    ChessAPI();
    ~ChessAPI();

    ChessList getWhiteChess() const { return listWhiteChess; }
    ChessList getBlackChess() const { return listBlackChess; }

    MoveList getMoveList(Move from);
    MoveList getAttackList(Move from);
    Move checkMate(Color color);

    bool attack(Move from, Move to);
    bool move(Move from, Move to);

    ChessPiece* piece(Move pos);
};

#endif // CHESSAPI_H
