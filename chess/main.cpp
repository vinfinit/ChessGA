#include <QDebug>

#include <iostream>

#include "chesscontroller.h"

int main()
{
    auto chess = new ChessController();

    foreach (auto item, chess->getWhiteChess()) {
        std::cout << static_cast<short>(item->getType()) << " {" << item->getCurPos()[0] << ", " << item->getCurPos()[1] << '}' << std::endl;
    }

    return 0;
}
