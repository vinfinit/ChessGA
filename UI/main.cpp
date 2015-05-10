#include <QApplication>
#include <QQmlApplicationEngine>
#include <QQmlComponent>

#include <QWidget>

#include "chesswrapper.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qmlRegisterType<ChessWrapper>("com.bsu.chessGA", 1, 0, "Wrapper");

    QQmlApplicationEngine engine;
    engine.load(QUrl(QStringLiteral("qrc:/main.qml")));

    return app.exec();
}
