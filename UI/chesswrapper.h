#ifndef CHESSWRAPPER_H
#define CHESSWRAPPER_H

#include "../chess/chessapi.h"

#include <QObject>
#include <QVector>

class ChessWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVector<ChessPiece*> whiteChess READ whiteChess WRITE setWhiteChess NOTIFY whiteChessChanged)
    Q_PROPERTY(QVector<int> whitePawn READ whitePawn WRITE setWhitePawn NOTIFY whitePawnChanged)
//    Q_PROPERTY(QVector<ChessPiece*> blackChess READ blackChess WRITE setBlackChess NOTIFY blackChessChanged)
public:
    ChessAPI *api;
    explicit ChessWrapper(QObject *parent = 0);
    ~ChessWrapper();

    QVector<ChessPiece*> whiteChess();
    void setWhiteChess(QVector<ChessPiece*> newVector);
//    QVector<ChessPiece*> blackChess();

    QVector<int> whitePawn() { return {7,8,9}; }
    void setWhitePawn(QVector<int>) {}

signals:
    void whiteChessChanged();
    void whitePawnChanged();
//    void blackChessChanged();
    void updateBoard();

public slots:

private:
//    QVector<ChessPiece*> _whiteChess;
//    QVector<ChessPiece*> _blackChess;
};

#endif // CHESSWRAPPER_H
