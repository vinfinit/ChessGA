#include "client.h"
#include <QDebug>
#include <QTextCodec>

Client::Client(QObject *parent) : QObject(parent), _socket(nullptr)
{ run(); }

Client::~Client() {}

void Client::run() {
    _socket = new QTcpSocket(this);
    connect(_socket, SIGNAL(connected()), this, SLOT(connected()));
    connect(_socket, SIGNAL(disconnected()), this, SLOT(disconnected()));
    connect(_socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
    connect(_socket, SIGNAL(bytesWritten(qint64)), this, SLOT(bytesWritten(qint64)));

    qDebug() << "Connecting,..";

    _socket->connectToHost("127.0.0.1", 1234);

//    if(!_socket->waitForDisconnected(1000))
//    {
//        qDebug() << "Error: " << _socket->errorString();
//    }
}

void Client::connected()
{
    qDebug() << "Connected!";

    _socket->write("I connected :)");
}

void Client::disconnected()
{
    qDebug() << "Disconnected!";
}

void Client::bytesWritten(qint64 bytes)
{
    qDebug() << "We wrote: " << bytes;
}

void Client::readyRead()
{
    qDebug() << "Reading...";
    QByteArray arr = _socket->readAll();
    QString str = QTextCodec::codecForMib(106)->toUnicode(arr);
    qDebug() << "str: " << str;
    if (str.length() == 7) {
        _from = {str.split(' ')[0].toInt(), str.split(' ')[1].toInt()};
        _to = {str.split(' ')[2].toInt(), str.split(' ')[3].toInt()};
        qDebug() << "from: " << _from[0] << _from[1] << "to: " << _to[0] << _to[1];
    }
}

void Client::move(Move to, Move from) {
    QString str;
    str.append(QString::number(to[0]) + ' ' + QString::number(to[1]) + ' ' +
            QString::number(from[0]) + ' ' + QString::number(from[1]));
    qDebug() << "In client move: " << str;
    _socket->write(str.toUtf8());
}

