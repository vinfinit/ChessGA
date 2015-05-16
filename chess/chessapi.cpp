#include "chessapi.h"
#include <set>

ChessAPI::ChessAPI() :
    next(Color::White), res(ChessRes::None)
{
    listWhiteChess = init(Color::White);
    listBlackChess = init(Color::Black);
}

ChessAPI::ChessAPI(const ChessAPI& api) {
    listWhiteChess = api.getWhiteChess();
    listBlackChess = api.getBlackChess();
}

ChessAPI::~ChessAPI() {
    listBlackChess.clear();
    listWhiteChess.clear();
}

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
            for (auto i : moveList) {
                item->move(i);
                if (checkMate(next).size())
                    blockList.push_back(i);
                item->move(from);
            }
            break;
        }

    // remove from moveList blockList values
    for (auto move : blockList)
        moveList.erase(std::remove(moveList.begin(), moveList.end(), move), moveList.end());

    return moveList;
}

MoveList ChessAPI::getAttackList(Move from) {
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    ChessPiece* tmp;
    MoveList attackList, blockList;

    for (auto item : list)
        if (item->getCurPos() == from) {
            attackList = mutableAttack(item);
            for (auto i : attackList) {
                tmp = piece(i);
                this->removeChessPiece(i);
                item->move(i);
                if (checkMate(next).size())
                    blockList.push_back(i);
                item->move(from);
                (next == Color::White ? listBlackChess : listWhiteChess).push_back(tmp);
            }
            break;
        }

    // remove from attackList blockList values
    for (auto move : blockList)
        attackList.erase(std::remove(attackList.begin(), attackList.end(), move), attackList.end());

    return attackList;
}

MoveList ChessAPI::getCastling(Move from) {
    MoveList res;
    auto n = next == Color::White ? STARTFIELD : ENDFIELD;
    auto king = piece(from);

    auto leftRook = piece({STARTFIELD, n});
    auto rightRook = piece({ENDFIELD, n});
    auto leftCheck = false, rightCheck = false;

    Move left1 = {STARTFIELD + 1, n}, left2 = {STARTFIELD + 2, n}, left3 = {STARTFIELD + 3, n},
            right1 = {ENDFIELD - 1, n}, right2 = {ENDFIELD - 2, n};
    Move posKing = {ENDFIELD - 3, n};

    if (from == posKing && king) {
        if (king->isEnabled() && king->getType() == ChessType::King && king->getColor() == next) {
            for (auto move : getMoveList(king->getCurPos())) {
                if (move == left3 && !piece(left1) && !piece(left2)) leftCheck = true;
                if (move == right2 && !piece(right1)) rightCheck = true;
            }

            if (leftCheck)
                if (leftRook->getType() == ChessType::Rook
                        && leftRook->isEnabled()) res.push_back(left2);

            if (rightCheck)
                if (rightRook->getType() == ChessType::Rook
                        && rightRook->isEnabled()) res.push_back(right1);

        } else {
            return {};
        }
    }
    return res;
}

//////////////////////////////////////////////////////////////////////////////////////////////

bool ChessAPI::move(Move from, Move to) {
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    for (auto item : list)
        if (item->getCurPos() == from)
            for (auto move : getMoveList(from))
                if (to == move) {
                    item->move(to);
                    item->setEnable(false);
                    next = next == Color::White ? Color::Black : Color::White;
                    checkImprovePawn();
                    return true;
                }
    return false;
}

bool ChessAPI::attack(Move from, Move to) {
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    for (auto item : list)
        if (item->getCurPos() == from)
            for (auto move : getAttackList(from))
                if (to == move) {
                    this->removeChessPiece(to);
                    item->move(to);
                    item->setEnable(false);
                    next = next == Color::White ? Color::Black : Color::White;
                    checkImprovePawn();
                    return true;
                }
    return false;
}

bool ChessAPI::castle(Move from, Move to) {
    ChessList list = next == Color::White ? listWhiteChess : listBlackChess;
    for (auto item : list)
        if (item->getCurPos() == from)
            for (auto move : getCastling(from))
                if (to == move) {
                    item->move(to);
                    item->setEnable(false);
                    if (from[0] - to[0] > 0) piece({STARTFIELD, from[1]})->move({STARTFIELD + 3, from[1]});
                    else piece({ENDFIELD, from[1]})->move({ENDFIELD - 2, from[1]});
                    next = next == Color::White ? Color::Black : Color::White;
                    return true;
                }
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

    list.clear();
    list = color == Color::White ? listBlackChess : listWhiteChess;

    next = next == Color::White ? Color::Black : Color::White;
    for (auto chess : list) {
        for (auto move : mutableAttack(chess)) {
            if (move == kingPos) {
                next = next == Color::White ? Color::Black : Color::White;
                piece(kingPos)->setEnable(false);
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
