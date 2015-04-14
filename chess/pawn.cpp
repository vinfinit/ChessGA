#include "pawn.h"

const int StartWhitePawn = 1;
const int StartBlackPawn = 6;

Pawn::~Pawn() {}

MoveList Pawn::permissibleMove() {
    int nextMove = 1;
    MoveList list;
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
        list.push_back(tmp);
        tmp.clear();
    }
    return list;
}
