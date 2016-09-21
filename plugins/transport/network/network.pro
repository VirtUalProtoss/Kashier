
CONFIG += c++11 plugin

QT += network
QT -= gui

TEMPLATE = lib
DESTDIR  = ../../../../bin/plugins
DEPENDPATH += ../../../../lib
INCLUDEPATH += . \
    ../../../common \
    ../../../common/queue

HEADERS += socketadapter.h \
    transportnetwork.h

SOURCES += socketadapter.cpp \
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

VERSION = 0.1.0
