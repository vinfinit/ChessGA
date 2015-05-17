#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include "../chess/chesspiece.h"

class Server : public QObject
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    ~Server();

    void move(Move to, Move from);
    MoveList getMove();
signals:

public slots:
    void newConnection();
    void readyRead();

private:
    QTcpServer *_server;
    QTcpSocket *_client;

    Move _from;
    Move _to;
};

#endif // SERVER_H
