#include "chesspiece.h"

ChessPiece::ChessPiece(ChessType type, Move curPos, Color color) :
    type(type),
    curPos(curPos),
    color(color) {}

ChessPiece::~ChessPiece() {
    curPos.clear();
}

// game field 8*8
bool ChessPiece::checkBorder(Move pos) {
    if (pos[0] >= STARTFIELD && pos[0] <= ENDFIELD)
        if (pos[1] >= STARTFIELD && pos[1] <= ENDFIELD)
            return true;
    return false;
}

MoveList ChessPiece::getBlockMove(Move blockMove, MoveList curMoveList) {
    MoveList res;

    for (auto move : curMoveList)
        if (move == blockMove)
            res.push_back(move);

    return res;
}


MoveList ChessPiece::getAttackMove(MoveList curMoveList) {
    MoveList moveList = permissibleMove();
    MoveList attackList;

    for (auto move : moveList)
        if (std::find(curMoveList.begin(), curMoveList.end(), move) == curMoveList.end())
            attackList.push_back(move);

    return attackList;
}
