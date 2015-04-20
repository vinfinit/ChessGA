#include "chesswrapper.h"

ChessWrapper::ChessWrapper(QObject *parent) : QObject(parent)
{
    api = new ChessAPI();
}

ChessWrapper::~ChessWrapper()
{

}

