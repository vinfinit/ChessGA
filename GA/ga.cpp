#include "ga.h"
#include <QDebug>
#include <vector>
#include <ctime>

const int POPULATION = 20;
const int MAX_ITERATION = 100;

GA::GA(Color color) :
    _api(nullptr), _color(color), _first(false)
{
    _api = new ChessAPI();
    _first = _color == Color::White ? true : false;
}

GA::~GA() { delete _api; }

Color GA::color() { return _color; }

MoveList GA::move(Move from, Move to) {
    qDebug() << "GA move in GA\n";
    if (_first) return startGeneration();
    if (_api->attack(from, to) || _api->move(from, to) || _api->castle(from, to)) return startGeneration();
    else return {};
}

MoveList GA::startGeneration() {
    _first = false;
    qDebug() << "GA color: " << (_color == Color::White ? "white" : "black");
    qDebug() << "APP color: " << (_api->getColor() == Color::White ? "white" : "black");
    if (_color != _api->getColor()) return {};
    return generation();
}

MoveList GA::generation() {
    qDebug() << "generation";
    auto engine = std::default_random_engine{std::random_device{}()};
    std::vector<MoveList> maskMove;
    Move from, to;
    MoveList list;
    int i = 0;

    while (i < MAX_ITERATION) {
        from.clear();
        to.clear();
        list.clear();
        from = generateMove();

        if (_api->getAttackList(from).size()) list = _api->getAttackList(from);
        else if (_api->getCastling(from).size()) list = _api->getCastling(from);
        else if (_api->getMoveList(from).size()) list = _api->getMoveList(from);
//qDebug() << "list size: " << list.size() << from[0] << from[1];
        if (list.size()) {
            to = list[engine() % list.size()];

            maskMove.push_back({from, to});
            if (maskMove.size() >= POPULATION) break;
        }
        i++;
        if (from.size() == 2 && to.size() == 2)
            qDebug() << "in loop " << from[0] << from[1] << to[0] << to[1] << " iterator: " << i << "mask size: " << maskMove.size();
    }
    qDebug() << "list size: " << maskMove.size();
    if (!maskMove.size() && _api->getRes() == ChessRes::None) {
        qDebug() << "kostil";
        auto list = _color == Color::White ? _api->getWhiteChess() : _api->getBlackChess();
        for (auto chess : list) {
            from = chess->getCurPos();
            if (_api->getAttackList(from).size()) {
                to = _api->getAttackList(from)[0];
                _api->attack(from, to);
                return {from, to};
            }
            else if (_api->getCastling(from).size()) {
                to = _api->getCastling(from)[0];
                _api->castle(from, to);
                return {from, to};
            }
            else if (_api->getMoveList(from).size()) {
                to = _api->getMoveList(from)[0];
                _api->move(from, to);
                return {from, to};
            }
        }
        return {};
    } else if (_api->getRes() != ChessRes::None) return {};

    int counter = engine() % maskMove.size();
    qDebug() << "Generation move from: " << maskMove[counter][0][0] << ' ' << maskMove[counter][0][1];
    qDebug() << "Generation move to: " << maskMove[counter][1][0] << ' ' << maskMove[counter][1][1];

    if (_api->attack(maskMove[counter][0], maskMove[counter][1])) ;
    else if (_api->castle(maskMove[counter][0], maskMove[counter][1])) ;
    else if (_api->move(maskMove[counter][0], maskMove[counter][1])) ;

    return maskMove[counter];
}

Move GA::generateMove() {
    std::random_device rd;
    std::mt19937 gen(rd());
    return {static_cast<int>(gen() % (ENDFIELD + 1)), static_cast<int>(gen() % (ENDFIELD + 1))};
}

int GA::fitness(ChessAPI *api) {
    auto list = _color == Color::White ? api->getWhiteChess() : api->getBlackChess();
    int weight = 0;
    foreach (auto piece, list) {
        for (auto attack : api->getAttackList(piece->getCurPos()))
            if (getWeight(api->piece(attack)) >= getWeight(piece))
                weight++;
        weight += (api->getMoveList(piece->getCurPos()).size() / 5);
        weight += getWeight(piece);
    }

    auto enemies = _color == Color::Black ? api->getWhiteChess() : api->getBlackChess();
    foreach (auto piece, enemies) {
        weight -= getWeight(piece);
    }

    return weight;
}

int GA::getWeight(ChessPiece *piece) {
    if (piece->getType() == ChessType::Pawn) return 1;
    if (piece->getType() == ChessType::Bishop || piece->getType() == ChessType::Knight) return 3;
    if (piece->getType() == ChessType::Rook) return 4;
    if (piece->getType() == ChessType::Queen) return 6;
    return 0;
}

void GA::enemyMove(ChessAPI *api) {
    auto list = _color == Color::Black ? api->getWhiteChess() : api->getBlackChess();
    int weight = 0;
    Move from, to;
    foreach (auto piece, list) {
        foreach (auto attack, api->getAttackList(piece->getCurPos())) {
            if (getWeight(api->piece(attack)) >= getWeight(piece)) {
                weight = getWeight(api->piece(attack));
                from = piece->getCurPos();
                to = attack;
            }
        }
        if (!from.size() || !to.size()) {
            foreach (auto move, api->getCastling(piece->getCurPos())) {
                from = piece->getCurPos();
                to = move;
            }
        }
    }

    if (!to.size() || !from.size()) {
        while (true) {
            from = generateMove();
            if (api->getMoveList(from).size()) {
                to = api->getMoveList(from)[0];
                break;
            }
        }
    }
    api->attack(from, to);
    api->castle(from, to);
    api->move(from, to);
}
