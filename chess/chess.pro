#-------------------------------------------------
#
# Project created by QtCreator 2015-04-14T16:09:06
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = chess
CONFIG   -= app_bundle

CONFIG += c++11

TEMPLATE = app


SOURCES += main.cpp \
    chesspiece.cpp \
    pawn.cpp \
    king.cpp \
    queen.cpp \
    bishop.cpp \
    rook.cpp

HEADERS += \
    chesspiece.h \
    pawn.h \
    king.h \
    queen.h \
    bishop.h \
    rook.h
