#include "chesswrapper.h"

ChessWrapper::ChessWrapper(QObject *parent) : QObject(parent)
{
    api = new ChessAPI();
    emit updateBoard();
}

ChessWrapper::~ChessWrapper() {}

QVector<ChessPiece*> ChessWrapper::whiteChess() {
    return {new Bishop({0, 0}, Color::Black)};
}

void ChessWrapper::setWhiteChess(QVector<ChessPiece *> newVector) {
    ;
}
