#include "pawn.h"

const int StartWhitePawn = 1;
const int StartBlackPawn = 6;

Pawn::~Pawn() {}

MoveList Pawn::permissibleMove() {
    int nextMove = 1;
    MoveList moveList;
    Move move;
    if (color == Color::White) {
        move.push_back(curPos[1] + nextMove);
        if (curPos[1] == StartWhitePawn) move.push_back(curPos[1] + 2 * nextMove);
    } else if (color == Color::Black) {
        move.push_back(curPos[1] - nextMove);
        if (curPos[1] == StartBlackPawn) move.push_back(curPos[1] - 2 * nextMove);
    }
    Move tmp;
    for (MoveType i : move) {
        tmp.push_back(curPos[0]);
        tmp.push_back(i);
        if (checkBorder(tmp)) moveList.push_back(tmp);
        tmp.clear();
    }
    return moveList;
}

MoveList Pawn::getAttackMove(MoveList) {
    auto i = color == Color::White ? 1 : -1;
    MoveList attackList;
    attackList.push_back({curPos[0] + i, curPos[1] + i});
    attackList.push_back({curPos[0] - i, curPos[1] + i});
    return attackList;
}

MoveList Pawn::getBlockMove(Move blockMove, MoveList curMoveList) {
    MoveList res;
    Move tmp;

    for (auto move : curMoveList)
        if (move == blockMove)
            res.push_back(move);

    if (curMoveList.size() == 2 && res.size() > 0) {
        tmp.push_back(curPos[0]);
        if (color == Color::White)
            tmp.push_back(curPos[1] + 2);
        if (color == Color::Black)
            tmp.push_back(curPos[1] - 2);
        res.push_back(tmp);
    }

    return res;
}
