#-------------------------------------------------
#
# Project created by QtCreator 2016-01-29T09:32:58
#
#-------------------------------------------------

QT       += core network



TARGET = Kashier
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp \
    objectmanager.cpp

HEADERS += \
    objectmanager.h

include(client/client.pri)
include(server/server.pri)
