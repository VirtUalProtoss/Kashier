
CONFIG += c++11 plugin

QT += network

TEMPLATE = lib
DESTDIR  = ../../../../bin/plugins
DEPENDPATH += ../../../../lib
INCLUDEPATH += . \
    ../../../common \
    ../../../common/queue

HEADERS += isocketadapter.h \
    socketadapter.h \
    clientsocketadapter.h \
    serversocketadapter.h \
    transportnetwork.h

SOURCES += isocketadapter.cpp \
    socketadapter.cpp \
    clientsocketadapter.cpp \
    serversocketadapter.cpp \
    transportnetwork.cpp

CONFIG(debug, debug|release) {
    win32: LIBS += -L../../../../lib/
    unix: LIBS += -L../../../../lib/  #-Wl,-rpath,lib -Wl,-rpath,.
    TARGET = transport_networkd
} else {
    win32: LIBS += -L../../../../lib/
    unix: LIBS += -L../../../../lib/  #-Wl,-rpath,lib -Wl,-rpath,.
    TARGET = transport_network
} # CONFIG(debug, debug|release)

VERSION = 0.0.1
