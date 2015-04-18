#include "knight.h"

Knight::~Knight() {}

MoveList Knight::permissibleMove() {
    MoveList moveList;
    Move move;

    std::vector<int> tmp;                       // magic number, don't touch :)
    tmp.push_back(-2);
    tmp.push_back(-1);
    tmp.push_back(1);
    tmp.push_back(2);

    for (auto i = 0; i <= ENDFIELD; i += 2 ) {
        move.push_back(curPos[0] + tmp[i / 2]);
        move.push_back(curPos[1] + (tmp[i / 2] > 0 ? 3 - tmp[i / 2] : 3 + tmp[i / 2]));
        if (checkBorder(move)) moveList.push_back(move);
        move.clear();

        move.push_back(curPos[0] + tmp[i / 2]);
        move.push_back(curPos[1] - (tmp[i / 2] > 0 ? 3 - tmp[i / 2] : 3 + tmp[i / 2]));
        if (checkBorder(move)) moveList.push_back(move);
        move.clear();
    }
    return moveList;
}

