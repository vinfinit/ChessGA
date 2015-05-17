TEMPLATE = app

QT += qml quick widgets network

CONFIG += c++11

SOURCES += main.cpp \
    chesswrapper.cpp \
    ../chess/bishop.cpp \
    ../chess/chessapi.cpp \
    ../chess/chesspiece.cpp \
    ../chess/king.cpp \
    ../chess/knight.cpp \
    ../chess/pawn.cpp \
    ../chess/queen.cpp \
    ../chess/rook.cpp \
    ../GA/ga.cpp \
    ../server/server.cpp \
    ../client/client.cpp

RESOURCES += qml.qrc \
    images.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    chesswrapper.h \
    ../chess/bishop.h \
    ../chess/chessapi.h \
    ../chess/chesspiece.h \
    ../chess/king.h \
    ../chess/knight.h \
    ../chess/pawn.h \
    ../chess/queen.h \
    ../chess/rook.h \
    ../GA/ga.h \
    ../server/server.h \
    ../client/client.h

SUBDIRS += \
    ../chess/chess.pro
