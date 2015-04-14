#include "king.h"

King::~King() {}

MoveList King::permissibleMove() {
    MoveList moveList;
    Move move;
    for (auto i = -1; i < 2; i++) {
        for (auto j = -1; j < 2; j++) {
            if (j == i && j == 0) continue;         // avoid move to the same cell
            move.push_back(curPos[0] + i);
            move.push_back(curPos[1] + j);
            if (checkBorder(move)) moveList.push_back(move);
            move.clear();
        }
    }
    return moveList;
}
