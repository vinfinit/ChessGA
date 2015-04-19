#include <QDebug>

#include <iostream>

#include "chessapi.h"

int main()
{
    auto chess = new ChessAPI();

//    foreach (auto item, chess->getWhiteChess()) {
//        std::cout << static_cast<short>(item->getType()) << " {" << item->getCurPos()[0] << ", " << item->getCurPos()[1] << '}' << std::endl;
//    }

//    foreach (auto move, chess->getMove({1, 0})) {
//        std::cout << move[0] << ' ' << move[1] << std::endl;
//    }

    chess->move({0, 1}, {0, 3});
    chess->move({0, 6}, {0, 4});

    chess->move({4, 1}, {4, 3});
    chess->move({7, 6}, {7, 4});

    chess->move({3, 0}, {6, 3});
    chess->move({0, 7}, {0, 5});
    foreach (auto move, chess->getMoveList({5, 0})) {
        std::cout << move[0] << ' ' << move[1] << std::endl;
    }

    return 0;
}
