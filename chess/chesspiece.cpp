#include "chesspiece.h"

ChessPiece::ChessPiece(Move curPos, Color color) :
    curPos(curPos), color(color) {}

ChessPiece::~ChessPiece() {}

// game field 8*8
bool ChessPiece::checkBorder(Move pos) {
    if (pos[0] >= STARTFIELD && pos[0] <= ENDFIELD)
        if (pos[1] >= STARTFIELD && pos[1] <= ENDFIELD)
            return true;
    return false;
}
