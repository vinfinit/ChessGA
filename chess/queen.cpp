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

MoveList Queen::getBlockMove(Move blockMove, MoveList curMoveList) {
    auto x = curPos[0] - blockMove[0];
    auto y = curPos[1] - blockMove[1];
    MoveList res;

    // bishop
    if (x < 0 && y < 0)
        for (auto move : curMoveList)
            if (move[0] > x && move[1] > y)
                res.push_back(move);

    if (x > 0 && y > 0)
        for (auto move : curMoveList)
            if (move[0] < x && move[1] < y)
                res.push_back(move);

    if (x < 0 && y > 0)
        for (auto move : curMoveList)
            if (move[0] > x && move[1] < y)
                res.push_back(move);

    if (x > 0 && y < 0)
        for (auto move : curMoveList)
            if (move[0] < x && move[1] > y)
                res.push_back(move);

    // rook
    if (x < 0 && !y)
        for (auto move : curMoveList)
            if (move[0] > x && move[1] == y)
                res.push_back(move);

    if (x > 0 && !y)
        for (auto move : curMoveList)
            if (move[0] < x && move[1] == y)
                res.push_back(move);

    if (!x && y > 0)
        for (auto move : curMoveList)
            if (move[0] == x && move[1] < y)
                res.push_back(move);

    if (!x && y < 0)
        for (auto move : curMoveList)
            if (move[0] == x && move[1] > y)
                res.push_back(move);

    return res;
}
