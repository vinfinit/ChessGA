#ifndef GA_H
#define GA_H

#include "../chess/chessapi.h"

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

    MoveList generateMove();
};

#endif // GA_H
