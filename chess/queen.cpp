#include "queen.h"

Queen::~Queen() {}

MoveList Queen::permissibleMove() {
    MoveList moveList;
    Move move;
    for (auto i = -ENDFIELD; i <= ENDFIELD; i++) {
        if (i) {
            move.push_back(curPos[0] + i);                  // main diag
            move.push_back(curPos[1] + i);
            if (checkBorder(move)) moveList.push_back(move);
            move.clear();

            move.push_back(curPos[0] + i);                  // sup diag
            move.push_back(curPos[1] - i);
            if (checkBorder(move)) moveList.push_back(move);
            move.clear();

            move.push_back(curPos[0]);                      // vertical
            move.push_back(curPos[1] + i);
            if (checkBorder(move)) moveList.push_back(move);
            move.clear();

            move.push_back(curPos[0] + i);                  // horizont
            move.push_back(curPos[1]);
            if (checkBorder(move)) moveList.push_back(move);
            move.clear();
        }
    }
    return moveList;
}
