#include <QDebug>

#include "king.h"
#include "pawn.h"
#include "bishop.h"
#include "queen.h"
#include "rook.h"
#include "knight.h"

int main()
{
    auto *king = new Knight({7,4}, Color::Black);
    MoveList list = king->permissibleMove();
    for (auto i : list) {
        qDebug() << i[0] << i[1] << ' ';
    }

    return 0;
}
