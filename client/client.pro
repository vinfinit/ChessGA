#-------------------------------------------------
#
# Project created by QtCreator 2015-05-17T13:01:56
#
#-------------------------------------------------

QT       += core network

QT       -= gui

TARGET = client
CONFIG   += console c++11
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    client.cpp

HEADERS += \
    client.h \
    ../chess/chesspiece.h
