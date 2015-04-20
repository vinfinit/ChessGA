#ifndef CHESSWRAPPER_H
#define CHESSWRAPPER_H

#include <QObject>

class ChessWrapper : public QObject
{
    Q_OBJECT
public:
    explicit ChessWrapper(QObject *parent = 0);
    ~ChessWrapper();

signals:

public slots:
};

#endif // CHESSWRAPPER_H
