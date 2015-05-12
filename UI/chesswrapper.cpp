#include "chesswrapper.h"
#include <QDebug>

ChessWrapper::ChessWrapper(QObject *parent) :
    QObject(parent), _api(nullptr), _ga(nullptr), _players(0), _pos(0), _type(""), _color(""), _moveFrom(0)
{ _api = new ChessAPI(); }

ChessWrapper::~ChessWrapper() {}

int ChessWrapper::colorGA() { return _ga->color() == Color::White ? 0 : 1; }

void ChessWrapper::setColorGA(int color) {
    _ga = new GA(color == 0 ? Color::White : Color::Black);
    if (_ga->color() == Color::White) {
        auto list = _ga->move({}, {});
        if (!_api->move(list[0], list[1]))
            _api->attack(list[0], list[1]);
    }
    qDebug() << "setColorGA: " << (_ga->color() == Color::White ? "White" : "Black");
}

int ChessWrapper::players() { return _players; }

void ChessWrapper::setPlayers(int number) { _players = number; }

int ChessWrapper::pos() { return _pos; }

void ChessWrapper::setPos(int pos) {
    if (pos <= 63 && pos >= 0) _pos = pos;
}

int ChessWrapper::moveTo() { return _pos; }

void ChessWrapper::setMoveTo(int to) {
    qDebug() << "setMoveTo curColor: " << (_api->getColor() == Color::White ? "White" : "Black");
    qDebug() << "setMoveTo GAcolor: " << (_ga->color() == Color::White ? "White" : "Black");
    if (_api->attack({_moveFrom % 8, _moveFrom / 8}, {to % 8, to / 8}) ||
            _api->move({_moveFrom % 8, _moveFrom / 8}, {to % 8, to / 8}) ||
            _api->castle({_moveFrom % 8, _moveFrom / 8}, {to % 8, to / 8})) {
        if (!_players) {
            auto list = _ga->move({_moveFrom % 8, _moveFrom / 8}, {to % 8, to / 8});
            if (list.size() == 2 && list[0].size() == 2 && list[1].size() == 2)
                if (!_api->move(list[0], list[1]))
                    _api->attack(list[0], list[1]);
        }
    }
}

int ChessWrapper::moveFrom() { return _moveFrom; }

void ChessWrapper::setMoveFrom(int from) {
    if (from <= 63 && from >= 0) _moveFrom = from;
}

QString ChessWrapper::color() {
    auto piece = _api->piece({_pos % 8, _pos / 8});
    if (piece) {
        switch (piece->getColor()) {
        case Color::White:
            _color = "white";
            break;
        case Color::Black:
            _color = "black";
            break;
        default:
            _color = "white";
            break;
        }
        return _color;
    } else {
        return "";
    }
}

void ChessWrapper::setColor(QString) {}

QString ChessWrapper::type() {
    auto piece = _api->piece({_pos % 8, _pos / 8});
    if (piece) {
        switch (piece->getType()) {
        case ChessType::King:
            _type = "king";
            break;
        case ChessType::Queen:
            _type = "queen";
            break;
        case ChessType::Rook:
            _type = "rook";
            break;
        case ChessType::Bishop:
            _type = "bishop";
            break;
        case ChessType::Knight:
            _type = "knight";
            break;
        case ChessType::Pawn:
            _type = "pawn";
            break;
        default:
            _type = "pawn";
            break;
        }
        return _type;
    } else {
        return "";
    }
}

void ChessWrapper::setType(QString) {}

int ChessWrapper::res() {
    ChessRes tmp = _api->getRes();
    if (tmp == ChessRes::None) return 0;
    if (tmp == ChessRes::Draw) return 1;
    if (tmp == ChessRes::Mate) return 2;
    return 0;
}

void ChessWrapper::setRes(int) {}

QList<int> ChessWrapper::moveList() {
    MoveList list = _api->getMoveList({_pos % 8, _pos / 8});
    QList<int> res;
    for (auto move : list)
        res.push_back(move[0] + move[1] * 8);
    return res;
}

void ChessWrapper::setMoveList(QList<int>) {}

QList<int> ChessWrapper::attackList() {
    MoveList list = _api->getAttackList({_pos % 8, _pos / 8});
    QList<int> res;
    for (auto attack : list)
        res.push_back(attack[0] + attack[1] * 8);
    return res;
}

void ChessWrapper::setAttackList(QList<int>) {}

QList<int> ChessWrapper::castlingList() {
    MoveList list = _api->getCastling({_pos % 8, _pos / 8});
    QList<int> res;
    for (auto attack : list)
        res.push_back(attack[0] + attack[1] * 8);
    return res;
}

void ChessWrapper::setCastlingList(QList<int>) {}

int ChessWrapper::check() {
    Move check = _api->checkMate(Color::White);
    if (!check.size()) check = _api->checkMate(Color::Black);
    if (!check.size()) return -1;
    return check[0] + check[1] * 8;
}

void ChessWrapper::setCheck(int) {}
