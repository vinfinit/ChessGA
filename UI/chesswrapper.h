#ifndef CHESSWRAPPER_H
#define CHESSWRAPPER_H

#include "../chess/chessapi.h"

#include <QObject>
#include <QVector>

class ChessWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString curPiece READ curPiece WRITE setCurPiece NOTIFY curPieceChanged)
    Q_PROPERTY(QString curColor READ curColor WRITE setCurColor NOTIFY curColorChanged)
    Q_PROPERTY(int curPos READ curPos WRITE setCurPos NOTIFY curPosChanged)
public:
    ChessAPI *api;
    explicit ChessWrapper(QObject *parent = 0);
    ~ChessWrapper();

    QString curPiece();
    void setCurPiece(QString piece);

    int curPos();
    void setCurPos(int pos);

    QString curColor();
    void setCurColor(QString color);

signals:
    void curPieceChanged();
    void curPosChanged();
    void curColorChanged();

public slots:


private:

};

#endif // CHESSWRAPPER_H
