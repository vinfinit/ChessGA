#include "chesswrapper.h"
#include <QDebug>

ChessWrapper::ChessWrapper(QObject *parent) :
    QObject(parent), _api(nullptr), _pos(0), _type(""), _color("")
{ _api = new ChessAPI(); }

ChessWrapper::~ChessWrapper() {}

int ChessWrapper::pos() { return _pos; }

void ChessWrapper::setPos(int pos) {
    if (pos <= 63 && pos >= 0) _pos = pos;
    qDebug() << _pos << " in pos c++\n";
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

void ChessWrapper::setMoveList(QList<int> moveList) {
    ;
}
