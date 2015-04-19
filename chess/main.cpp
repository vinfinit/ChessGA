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

    chess->move({1, 0}, {2, 2});
    chess->move({0, 6}, {0, 4});
    foreach (auto move, chess->getMoves({2, 1})) {
        std::cout << move[0] << ' ' << move[1] << std::endl;
    }

    return 0;
}
