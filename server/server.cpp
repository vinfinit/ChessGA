#include "server.h"
#include <QTextCodec>

Server::Server(QObject *parent)
    : QObject(parent), _server(nullptr), _client(nullptr), _from({0, 0}), _to({0, 0})
{
    _server = new QTcpServer(this);

    connect(_server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if(!_server->listen(QHostAddress::Any, 1234)) {
        qDebug() << "Server could not start!";
    } else {
        qDebug() << "Server started!";
    }
}

Server::~Server() {}

void Server::newConnection()
{
    _client = _server->nextPendingConnection();

    connect(_client, SIGNAL(readyRead()), this, SLOT(readyRead()));

    _client->write("move to 1,2");
    _client->flush();

    _client->waitForBytesWritten(3000);

//    socket->close();
}

void Server::readyRead() {
    qDebug() << "Reading...";
    QByteArray arr = _client->readAll();
    QString str = QTextCodec::codecForMib(106)->toUnicode(arr);
    qDebug() << "str: " << str;
    if (str.length() == 7) {
        _from = {str.split(' ')[0].toInt(), str.split(' ')[1].toInt()};
        _to = {str.split(' ')[2].toInt(), str.split(' ')[3].toInt()};
        qDebug() << "from: " << _from[0] << _from[1] << "to: " << _to[0] << _to[1];
    }
}

void Server::move(Move to, Move from) {
    QString str;
    str.append(QString::number(to[0]) + ' ' + QString::number(to[1]) + ' ' +
            QString::number(from[0]) + ' ' + QString::number(from[1]));
    qDebug() << "In server move: " << str;
    if (_client) _client->write(str.toUtf8());
}

MoveList Server::getMove() {
    MoveList list;
    list.push_back(_from);
    list.push_back(_to);

    return list;
}
