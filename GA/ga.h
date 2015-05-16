#ifndef GA_H
#define GA_H

#include "../chess/chessapi.h"
#include <random>

class GA
{
public:
    GA(Color color);
    ~GA();

    MoveList move(Move to, Move from);
    Color color();
private:
    ChessAPI* _api;
    Color _color;
    bool _first;

    MoveList startGeneration();
    MoveList generation();
    Move generateMove();

    int fitness(ChessAPI* api);
    int getWeight(ChessPiece* piece);
    void enemyMove(ChessAPI* api);
};

#endif // GA_H
