#ifndef CHESSWRAPPER_H
#define CHESSWRAPPER_H

#include "../chess/chessapi.h"
#include "../GA/ga.h"

#include <QObject>

class ChessWrapper : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int pos READ pos WRITE setPos NOTIFY posChanged)
    Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
    Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    Q_PROPERTY(int res READ res WRITE setRes NOTIFY resChanged)
    Q_PROPERTY(int colorGA READ colorGA WRITE setColorGA NOTIFY colorGAChanged)
    Q_PROPERTY(int players READ players WRITE setPlayers NOTIFY playersChanged)

    Q_PROPERTY(int moveFrom READ moveFrom WRITE setMoveFrom NOTIFY moveFromChanged)
    Q_PROPERTY(int moveTo READ moveTo WRITE setMoveTo NOTIFY moveToChanged)

    Q_PROPERTY(QList<int> moveList READ moveList WRITE setMoveList NOTIFY moveListChanged)
    Q_PROPERTY(QList<int> attackList READ attackList WRITE setAttackList NOTIFY attackListChanged)
    Q_PROPERTY(QList<int> castlingList READ castlingList WRITE setCastlingList NOTIFY castlingListChanged)
    Q_PROPERTY(int check READ check WRITE setCheck NOTIFY checkChanged)
    public:
        explicit ChessWrapper(QObject *parent = 0);
        ~ChessWrapper();

        int colorGA();
        void setColorGA(int color);

        int players();
        void setPlayers(int number);

        int pos();
        void setPos(int pos);

        int moveTo();
        void setMoveTo(int to);

        int moveFrom();
        void setMoveFrom(int from);

        int res();
        void setRes(int res);

        QString color();
        void setColor(QString color);

        QString type();
        void setType(QString type);

        QList<int> moveList();
        void setMoveList(QList<int> moveList);

        QList<int> attackList();
        void setAttackList(QList<int> attackList);

        QList<int> castlingList();
        void setCastlingList(QList<int> castlingList);

        int check();
        void setCheck(int);

    signals:
        void colorGAChanged();
        void posChanged();
        void moveToChanged();
        void moveFromChanged();
        void colorChanged();
        void typeChanged();
        void moveListChanged();
        void attackListChanged();
        void resChanged();
        void checkChanged();
        void playersChanged();
        void castlingListChanged();

    public slots:


    private:
        ChessAPI *_api;
        GA *_ga;
        int _players;

        int _pos;
        QString _type;
        QString _color;
        int _moveFrom;

        void restart();
};

#endif // CHESSWRAPPER_H
