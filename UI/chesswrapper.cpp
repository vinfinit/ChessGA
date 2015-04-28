#include "chesswrapper.h"

ChessWrapper::ChessWrapper(QObject *parent) : QObject(parent)
{
    api = new ChessAPI();
}

ChessWrapper::~ChessWrapper() {}

QString ChessWrapper::curPiece() {
    return "pawn";
}

int ChessWrapper::curPos() {
    return 12;
}

QString ChessWrapper::curColor() {
    return "white";
}

void ChessWrapper::setCurColor(QString color) {
    ;
}

void ChessWrapper::setCurPos(int pos) {
    ;
}

void ChessWrapper::setCurPiece(QString piece) {
    ;
}
