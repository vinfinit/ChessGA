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

enum class ChessRes {Mate, Draw, None};

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

    ChessRes res;
public:
    ChessAPI();
    ChessAPI(const ChessAPI& api);
    ~ChessAPI();

    ChessList getWhiteChess() const { return listWhiteChess; }
    ChessList getBlackChess() const { return listBlackChess; }

    MoveList getMoveList(Move from);
    MoveList getAttackList(Move from);
    MoveList getCastling(Move from);            // first move for king, second for rook

    Move checkMate(Color color);
    ChessRes getRes();
    Color getColor();
    ChessPiece* piece(Move pos);

    bool attack(Move from, Move to);
    bool move(Move from, Move to);
    bool castle(Move from, Move to);
};

#endif // CHESSAPI_H
