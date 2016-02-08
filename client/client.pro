
QT       += gui serialport network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = client
DEPENDPATH += .
INCLUDEPATH += .
OBJECTS_DIR = _build
DESTDIR  = ../bin

CONFIG += c++11

SOURCES += main.cpp \
    client.cpp \
    kashier.cpp \
    kkm.cpp \
    loginwindow.cpp \
    mainwindow.cpp \
    paymentwindow.cpp \
    settingswindow.cpp \
    shtrihprotocol.cpp \
    clientsocketadapter.cpp \
    ../common/isocketadapter.cpp \
    ../common/socketadapter.cpp \
    ../common/objectmanager.cpp

HEADERS  += \
    client.h \
    kashier.h \
    kkm.h \
    loginwindow.h \
    mainwindow.h \
    paymentwindow.h \
    settingswindow.h \
    clientsocketadapter.h \
    ../common/objectmanager.h \
    ../common/isocketadapter.h \
    ../common/socketadapter.h \
    shtrihprotocol.h

FORMS    += mainwindow.ui \
    loginwindow.ui \
    paymentwindow.ui \
    settingswindow.ui