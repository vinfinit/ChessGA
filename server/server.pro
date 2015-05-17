#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T12:50:43
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = server
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp

HEADERS += \
    server.h \
    ../chess/chesspiece.h

