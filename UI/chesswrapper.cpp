#include "chesswrapper.h"
#include <QApplication>

ChessWrapper::ChessWrapper(QObject *parent) : QObject(parent)
{
    api = new ChessAPI();
}

ChessWrapper::~ChessWrapper()
{

}

void ChessWrapper::close() {
    QApplication::quit();
}
