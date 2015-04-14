#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include <vector>

typedef std::vector<std::vector<int> > MoveList;
typedef std::vector<int> Move;
typedef std::vector<int>::size_type MoveType;

const int STARTFIELD = 0;
const int ENDFIELD = 7;

// white from 0 to 7, black vice versa
enum class Color {Black, White};

class ChessPiece
{
protected:
    Move curPos;
    Color color;
public:
    ChessPiece(Move curPos, Color color);
    ~ChessPiece();

    bool checkBorder(Move pos);
    virtual MoveList permissibleMove() = 0;
};

#endif // CHESSPIECE_H
