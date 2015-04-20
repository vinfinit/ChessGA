#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include <QWidget>

#include "chesswrapper.h"
//#include "../chess/chessapi.h"
//#include "../chess/chesspiece.h"
//#include "../chess/bishop.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
//    auto bishop = new Bishop({1,1}, Color::Black);
//    auto pawn = new Pawn({1,1}, Color::Black);
//    auto king = new King({1,1}, Color::Black);
//    auto api = new ChessAPI();

    qmlRegisterType<ChessWrapper>("com.bsu.chessGA", 1, 0, "ChessAPI");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
