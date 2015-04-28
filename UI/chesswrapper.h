#ifndef CHESSWRAPPER_H
#define CHESSWRAPPER_H

#include "../chess/chessapi.h"

#include <QObject>

class ChessWrapper : public QObject
{
    Q_OBJECT
        Q_PROPERTY(int pos READ pos WRITE setPos NOTIFY posChanged)
        Q_PROPERTY(QString color READ color WRITE setColor NOTIFY colorChanged)
        Q_PROPERTY(QString type READ type WRITE setType NOTIFY typeChanged)
    public:
        ChessAPI *api;
        explicit ChessWrapper(QObject *parent = 0);
        ~ChessWrapper();

        int pos();
        void setPos(int pos);

        QString color();
        void setColor(QString color);

        QString type();
        void setType(QString type);

    signals:
        void posChanged();
        void colorChanged();
        void typeChanged();

    public slots:


    private:
        int _pos;
        QString _type;
        QString _color;
};

#endif // CHESSWRAPPER_H
