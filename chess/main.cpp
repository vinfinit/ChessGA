#include <QDebug>

#include <iostream>

#include "chessapi.h"

int main()
{
    auto chess = new ChessAPI();

    foreach (auto item, chess->getWhiteChess()) {
        std::cout << static_cast<short>(item->getType()) << " {" << item->getCurPos()[0] << ", " << item->getCurPos()[1] << '}' << std::endl;
    }

    return 0;
}
