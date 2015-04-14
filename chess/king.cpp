#include "king.h"

King::~King() {}

MoveList King::permissibleMove() {
    MoveList moveList;
    Move move;
    for (int i = 0; i < 2; i ++) {
        for (int j = 0; j < 2; j++) {
            move.push_back(curPos[0] + i);
            move.push_back(curPos[1] + j);
            moveList.push_back(move);
            move.clear();
        }
    }
    return moveList;
}
