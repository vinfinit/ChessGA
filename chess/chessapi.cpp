#include "chessapi.h"
#include <set>

#include <iostream>

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

MoveList ChessAPI::getMoves(Move from) {
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
//    std::cout << "from " << from[0] << ' ' << from[1] << std::endl;
    for (auto item : list)
        if (item->getCurPos() == from)
            return mutableMove(item);
    return {};
}

MoveList ChessAPI::mutableMove(ChessPiece* chess) {
    MoveList blockMoveList, tmp;
    MoveList permissibleMove = chess->permissibleMove();
//    std::cout << permissibleMove[0][0] << ' ' << permissibleMove[0][1] << std::endl;
    for (auto move : permissibleMove) {
        for (auto white : listWhiteChess) {
            if (move == white->getCurPos()) {
                tmp = chess->getBlockMove(move, permissibleMove);
                std::copy(tmp.begin(), tmp.end(), std::back_inserter(blockMoveList));
                break;
            }
        }
        for (auto black : listBlackChess) {
            if (move == black->getCurPos()) {
                tmp = chess->getBlockMove(move, permissibleMove);
                std::copy(tmp.begin(), tmp.end(), std::back_inserter(blockMoveList));
                break;
            }
        }
        tmp.clear();
    }

//    for (auto move : permissibleMove) {
//        std::cout << move[0] << ' ' << move[1] << std::endl;
//    }

    // remove the same move from blockMoveList
    std::set<Move> blockSet(blockMoveList.begin(), blockMoveList.end());

    for (auto move : blockSet) {
        std::cout << "block " << move[0] << ' ' << move[1] << std::endl;
    }

    // remove from permissibleMove blockSet values
    for (auto move : blockSet)
        permissibleMove.erase(std::remove(permissibleMove.begin(), permissibleMove.end(), move), permissibleMove.end());

    return permissibleMove;
}

bool ChessAPI::move(Move from, Move to) {
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    for (auto item : list)
        if (item->getCurPos() == from)
            for (auto move : getMoves(from))
                if (to == move) {
                    item->move(to);
                    next = next == Color::White ? Color::Black : Color::White;
                    std::cout << "move true" << std::endl;
                    return true;
                }
    std::cout << "move false" << std::endl;
    return false;
}
