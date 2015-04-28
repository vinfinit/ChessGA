#include <QDebug>

#include <iostream>

#include "chessapi.h"

int main()
{
    auto chess = new ChessAPI();

    chess->move({0, 1}, {0, 3});
    chess->move({0, 6}, {0, 4});

//    chess->move({4, 1}, {4, 3});
//    chess->move({7, 6}, {7, 4});

//    chess->move({3, 0}, {6, 3});
//    chess->move({0, 7}, {0, 5});
    foreach (auto move, chess->getMoveList({0, 0})) {
        std::cout << move[0] << ' ' << move[1] << std::endl;
    }

    return 0;
}
