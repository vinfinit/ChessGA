#include "chessapi.h"

ChessAPI::ChessAPI() :
    next(Color::White)
{
    listWhiteChess = init(Color::White);
    listBlackChess = init(Color::Black);
}

ChessAPI::~ChessAPI() {}

ChessList ChessAPI::init(Color color) {
    int n = color == Color::Black ? ENDFIELD : STARTFIELD;
    ChessList listChess;

    listChess.push_back(new King({ENDFIELD - 3, n}, color));
    listChess.push_back(new Queen({STARTFIELD + 3, n}, color));

    listChess.push_back(new Rook({STARTFIELD, n}, color));
    listChess.push_back(new Rook({ENDFIELD, n}, color));

    listChess.push_back(new Bishop({STARTFIELD + 2, n}, color));
    listChess.push_back(new Bishop({ENDFIELD - 2, n}, color));

    listChess.push_back(new Knight({STARTFIELD + 1, n}, color));
    listChess.push_back(new Knight({ENDFIELD - 1, n}, color));

    for (auto i = 0; i < 8; i++) {
        listChess.push_back(new Pawn({STARTFIELD + i, n - 1 > 0 ? n - 1 : n + 1}, color));
    }
    return listChess;
}

MoveList ChessAPI::getMove(Move from) {
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    for (auto item : list)
        if (item->getCurPos() == from)
            return mutableMove(item);
    return {};
}

MoveList ChessAPI::mutableMove(ChessPiece* chess) {

}
