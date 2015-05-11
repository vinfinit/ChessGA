#include "chessapi.h"
#include <set>
#include <QDebug>

#include <iostream>

ChessAPI::ChessAPI() :
    next(Color::White), res(ChessRes::None)
{
    qDebug() << "Init\n";
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
///////////////////////////////////////////////////////////////////////////////////////////
MoveList ChessAPI::getMoveList(Move from) {
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    MoveList moveList, blockList;

    for (auto item : list)
        if (item->getCurPos() == from) {
            moveList = mutableMove(item);
            qDebug() << "moveList all good\n";
            for (auto i : moveList) {
                item->move(i);
                if (checkMate(next).size()) {
                    qDebug() << "King was dangerous !!!!!!!!!!\n";
                    blockList.push_back(i);
                }
                item->move(from);
                qDebug() << i[0] << ' ' << i[1] << '\n';
            }
            break;
        }

    // remove from moveList blockList values
    for (auto move : blockList) {
        qDebug() << "Block list new " << move[0] << ' ' << move[1] << '\n';
        if (next == Color::White)
            qDebug() << "white\n";
        else qDebug() << "Black\n";
        moveList.erase(std::remove(moveList.begin(), moveList.end(), move), moveList.end());
    }

    return moveList;
}

MoveList ChessAPI::getAttackList(Move from) {
//    if (getRes() != ChessRes::None) return {};
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    ChessPiece* tmp;
    MoveList attackList, blockList;

    for (auto item : list)
        if (item->getCurPos() == from) {
            attackList = mutableAttack(item);
            qDebug() << "attackList all good\n";
            for (auto i : attackList) {
                tmp = piece(i);
                this->removeChessPiece(i);
                item->move(i);
                if (checkMate(next).size()) {
                    qDebug() << "King was dangerous !!!!!!!!!!\n";
                    blockList.push_back(i);
                }
                item->move(from);
                (next == Color::White ? listBlackChess : listWhiteChess).push_back(tmp);
                qDebug() << i[0] << ' ' << i[1] << '\n';
            }
            break;
        }

    // remove from attackList blockList values
    for (auto move : blockList) {
        qDebug() << "Block list new " << move[0] << ' ' << move[1] << '\n';
        if (next == Color::White)
            qDebug() << "white\n";
        else qDebug() << "Black\n";
        attackList.erase(std::remove(attackList.begin(), attackList.end(), move), attackList.end());
    }

    return attackList;
}
//////////////////////////////////////////////////////////////////////////////////////////////

bool ChessAPI::move(Move from, Move to) {
//    if (getRes() != ChessRes::None) return {};
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    for (auto item : list)
        if (item->getCurPos() == from)
            for (auto move : getMoveList(from))
                if (to == move) {
                    item->move(to);
                    next = next == Color::White ? Color::Black : Color::White;
                    std::cout << "move true" << std::endl;
                    checkImprovePawn();
                    return true;
                }
    std::cout << "move false" << std::endl;
    return false;
}

bool ChessAPI::attack(Move from, Move to) {
//    if (getRes() != ChessRes::None) return {};
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    for (auto item : list)
        if (item->getCurPos() == from)
            for (auto move : getAttackList(from))
                if (to == move) {
                    this->removeChessPiece(to);
                    item->move(to);
                    next = next == Color::White ? Color::Black : Color::White;
                    std::cout << "attack true" << std::endl;
                    checkImprovePawn();
                    return true;
                }
    std::cout << "attack false" << std::endl;
    return false;
}

MoveList ChessAPI::mutableMove(ChessPiece* chess) {
    MoveList blockMoveList, tmp;
    MoveList permissibleMove = chess->permissibleMove();
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

    // remove the same move from blockMoveList
    std::set<Move> blockSet(blockMoveList.begin(), blockMoveList.end());

    // remove from permissibleMove blockSet values
    for (auto move : blockSet)
        permissibleMove.erase(std::remove(permissibleMove.begin(), permissibleMove.end(), move), permissibleMove.end());

    return permissibleMove;
}

MoveList ChessAPI::mutableAttack(ChessPiece *chess) {
    MoveList attackList = chess->getAttackMove(mutableMove(chess));
    ChessList chessList = next == Color::White ? listBlackChess : listWhiteChess;
    MoveList res;

    for (auto move : attackList)
        for (auto chess : chessList)
            if (move == chess->getCurPos())
                res.push_back(move);

    return res;
}

ChessPiece* ChessAPI::piece(Move pos) {
    for (auto item : listBlackChess)
        if (item->getCurPos() == pos)
            return item;
    for (auto item : listWhiteChess)
        if (item->getCurPos() == pos)
            return item;
    return nullptr;
}

bool ChessAPI::removeChessPiece(Move pos) {
    std::cout << "in remove chess\n";
    ChessPiece* chess = nullptr;
    for (auto item : listBlackChess)
        if(item->getCurPos() == pos)
            chess = item;
    for (auto item : listWhiteChess)
        if(item->getCurPos() == pos)
            chess = item;
    if (chess) {
        listBlackChess.erase(std::remove(listBlackChess.begin(), listBlackChess.end(), chess), listBlackChess.end());
        listWhiteChess.erase(std::remove(listWhiteChess.begin(), listWhiteChess.end(), chess), listWhiteChess.end());
        return true;
    }
    return false;
}

bool ChessAPI::checkImprovePawn() {
    std::cout << "in checkImprovePawn\n";
    ChessPiece* chess = nullptr;
    for (auto item : listBlackChess)
        if (item->getType() == ChessType::Pawn && item->getCurPos()[1] == 0)
            chess = item;
    for (auto item : listWhiteChess)
        if (item->getType() == ChessType::Pawn && item->getCurPos()[1] == 7)
            chess = item;
    if (chess) {
        if (chess->getColor() == Color::Black) {
            listBlackChess.push_back(new Queen(chess->getCurPos(), chess->getColor()));
            listBlackChess.erase(std::remove(listBlackChess.begin(), listBlackChess.end(), chess), listBlackChess.end());
        } else {
            listWhiteChess.push_back(new Queen(chess->getCurPos(), chess->getColor()));
            listWhiteChess.erase(std::remove(listWhiteChess.begin(), listWhiteChess.end(), chess), listWhiteChess.end());
        }
        return true;
    }
    return false;
}

Move ChessAPI::checkMate(Color color) {
    ChessList list = color == Color::White ? listWhiteChess : listBlackChess;
    Move kingPos;

    for (auto chess : list)
        if (chess->getType() == ChessType::King)
            kingPos = chess->getCurPos();
    qDebug() << "in checkMate king pos " << kingPos[0] << ' ' << kingPos[1] << '\n';

    list.clear();
    list = color == Color::White ? listBlackChess : listWhiteChess;

    next = next == Color::White ? Color::Black : Color::White;
    for (auto chess : list) {
        for (auto move : mutableAttack(chess)) {
            qDebug() << "in checkMate " << move[0] << ' ' << move[1] << '\n';
            if (move == kingPos) {
                next = next == Color::White ? Color::Black : Color::White;
                return kingPos;
            }
        }
    }
    next = next == Color::White ? Color::Black : Color::White;
    return {};
}

ChessRes ChessAPI::getRes() {
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    Move kingPos;
    res = ChessRes::Draw;

    for (auto item : list) {
        if ((getMoveList(item->getCurPos())).size() || getAttackList(item->getCurPos()).size()) {
            res = ChessRes::None;
            return res;
        }
        if (item->getType() == ChessType::King) kingPos = item->getCurPos();
    }

    if (checkMate(next).size()) {
        res = ChessRes::Mate;
        return res;
    }

    return res;
}

Color ChessAPI::getColor() {
    return next;
}
