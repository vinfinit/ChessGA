#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>
#include <QQmlContext>

#include <QWidget>

#include "chesswrapper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<ChessWrapper>("com.bsu.chessGA", 1, 0, "Wrapper");

//    auto chessWrapper = new ChessWrapper();

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));
//    engine.rootContext()->setContextProperty("wrapper", chessWrapper);

    return app.exec();
}
