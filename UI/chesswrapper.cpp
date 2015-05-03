#include "chesswrapper.h"
#include <QDebug>

ChessWrapper::ChessWrapper(QObject *parent) :
    QObject(parent), _api(nullptr), _pos(0), _type(""), _color(""), _moveFrom(0)
{ _api = new ChessAPI(); }

ChessWrapper::~ChessWrapper() {}

int ChessWrapper::pos() { return _pos; }

void ChessWrapper::setPos(int pos) {
    if (pos <= 63 && pos >= 0) _pos = pos;
    qDebug() << _pos << " in pos c++\n";
}

int ChessWrapper::moveTo() { return _pos; }

void ChessWrapper::setMoveTo(int to) {
    _api->move({_moveFrom % 8, _moveFrom / 8}, {to % 8, to / 8});
}

int ChessWrapper::moveFrom() { return _moveFrom; }

void ChessWrapper::setMoveFrom(int from) {
    if (from <= 63 && from >= 0) _moveFrom = from;
    qDebug() << _moveFrom << " in setMoveFrom c++\n";
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
