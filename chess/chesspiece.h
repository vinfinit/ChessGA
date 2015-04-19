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

enum class ChessType {King, Queen, Rook, Bishop, Knight, Pawn};

class ChessPiece
{
protected:
    ChessType type;
    Move curPos;
    Color color;
public:
    ChessPiece(ChessType type, Move curPos, Color color);
    ~ChessPiece();

    bool checkBorder(Move pos);
    virtual MoveList permissibleMove() = 0;
    virtual MoveList getBlockMove(Move blockMove, MoveList curMoveList);        // don't override for king, knight and pawn
    virtual MoveList getAttackMove(MoveList curMoveList);                       // don't override for king and knight

    Move getCurPos() const { return curPos; }
    ChessType getType() const { return type; }

    void move(Move to) { curPos = to; }
};

#endif // CHESSPIECE_H
