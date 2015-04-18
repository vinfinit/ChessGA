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
