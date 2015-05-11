QT       += core
QT       -= gui

CONFIG   -= app_bundle
CONFIG += c++11

TEMPLATE = app

SOURCES += main.cpp \
    ../chess/bishop.cpp \
    ../chess/chessapi.cpp \
    ../chess/chesspiece.cpp \
    ../chess/king.cpp \
    ../chess/knight.cpp \
    ../chess/pawn.cpp \
    ../chess/queen.cpp \
    ../chess/rook.cpp \
    ga.cpp

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    ../chess/bishop.h \
    ../chess/chessapi.h \
    ../chess/chesspiece.h \
    ../chess/king.h \
    ../chess/knight.h \
    ../chess/pawn.h \
    ../chess/queen.h \
    ../chess/rook.h \
    ga.h

